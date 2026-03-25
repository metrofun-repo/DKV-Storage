#include "ReplicationService.h"

#include <chrono>

#include "domain/replication/ReplicationResponsePayload.h"

#include "application/api/builders/ExternalResponseBuilder.h"
#include "application/api/validation/ExternalRequestValidator.h"

#include "application/cluster/protocol/ClusterError.h"
#include "application/cluster/protocol/InternalRequest.h"
#include "application/cluster/mapping/TransportToReplication.h"
#include "application/cluster/builders/InternalResponseBuilder.h"
#include "application/cluster/validation/InternalValidator.h"

#include "infrastructure/transport/error/TransportError.h"

namespace app::cluster::services {

using ExternalRequest          = api::dto::ExternalRequest;
using ExternalResponse         = api::dto::ExternalResponse;
using ExternalResponseBuilder  = api::builders::ExternalResponseBuilder;
using ExternalRequestValidator = api::validation::ExternalRequestValidator;

using ReplicationPayload        = protocol::ReplicationPayload;    
using InternalRequest           = protocol::InternalRequest;
using InternalResponse          = protocol::InternalResponse;
using InternalResponseBuilder   = builders::InternalResponseBuilder;
using InternalValidator = validation::InternalValidator;

using ReplicationResponsePayload = domain::replication::ReplicationResponsePayload;
using ReplicationFanoutResult    = domain::replication::ReplicationFanoutResult;
using ReplicationError           = domain::replication::error::ReplicationError;
using ReplicationErrorCode       = domain::replication::error::ReplicationErrorCode;
using NodeError                  = domain::replication::error::NodeError<ReplicationError>;

using ReplicationResult       = core::types::Expected<void, error::AppError>;

ReplicationService::ReplicationService(
        cluster::state::ClusterState& state,
        app::types::StorageService& storage,
        infra::transport::senders::HttpClusterSender& sender)
    : clusterState(state) 
    , storage(storage)
    , sender(sender) 
{}

bool ReplicationService::quorumReached(const ReplicationFanoutResult& fanout) const
{
    const std::size_t quorum = clusterState.getQuorumSize();
    std::size_t acks = 1; // self

    for(auto& node : fanout.acknowledged)
    {
        if(clusterState.isAlive(node))
            ++acks;
    }
    return acks >= quorum;
}

ReplicationFanoutResult ReplicationService::fanout(const ReplicationPayload& req)
{
    ReplicationFanoutResult result;
    result.acknowledged.reserve(clusterState.getKnownNodes().size());
    result.failed.reserve(clusterState.getKnownNodes().size());

    InternalRequest request { InternalRequest::Type::Replication, req };

    for(auto& node : clusterState.getKnownNodes())
    {
        if(clusterState.isDead(node.nodeId)) continue;

        auto res = sender.send(request, node);
        
        if(!res.hasValue())
        {
            result.failed.emplace_back(NodeError{
                node.nodeId,
                { mapping::fromTransport(res.error().code), res.error().message }
            });
            continue;
        }
        auto response = res.value();

        auto validation = InternalValidator::validate<ReplicationResponsePayload, InternalResponse::Type::Replication>(response);
        if(!validation.hasValue())
        {
            result.failed.emplace_back(NodeError{
                node.nodeId,
                { ReplicationErrorCode::NodeInvalidResponse, validation.error().message }
            });
            continue;
        }

        auto& payload = std::get<ReplicationResponsePayload>(response.payload);
        if(!payload.applied)
        {
            result.failed.emplace_back(NodeError{ 
                node.nodeId,
                { ReplicationErrorCode::RemoteApplyFailed, payload.error.message }
            });
            continue;
        }
    
        result.acknowledged.emplace_back(node.nodeId);
    }
    return result;
}

template <typename Fn>
core::types::Expected<void, error::AppError> ReplicationService::replicationOperation(const ReplicationPayload& payload, Fn&& applyFn)
{
    auto apply = applyFn();
    if(!apply.hasValue())
    {
        return ReplicationResult::makeFailure(
            error::AppError { 
                error::AppErrorCode::StorageFailure,
                apply.error().message
            }
        );
    }
    
    if(!clusterState.quorumHealthy())
    {
        return ReplicationResult::makeFailure(
            error::AppError { 
                error::AppErrorCode::StorageFailure,//ReplicationErrorCode::ClusterNotHealthy, 
                "Cluster does not have quorum of alive nodes"
            }
        );      
    }

    auto fanoutResult = fanout(payload);

    bool reached = quorumReached(fanoutResult);

    if(!reached)
    {
        return ReplicationResult::makeFailure(
            error::AppError { 
                error::AppErrorCode::StorageFailure,//ReplicationErrorCode::QuorumNotReached,
                "Quorum not reached"
            }
        );  
    }

    return ReplicationResult::makeSuccess();   
}

ExternalResponse ReplicationService::replicate(const ExternalRequest& req)
{
    auto valid = ExternalRequestValidator::validate(req);
    if(!valid.hasValue())
    {
        return ExternalResponseBuilder::from(
            ReplicationResult::makeFailure(
                error::AppError { 
                    error::AppErrorCode::InvalidRequest,
                    valid.error().message
            })
        );        
    }

    const int64_t ts = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    app::types::VersionedValue value;
    if(req.operation == ExternalRequest::OperationType::Set)
    {
        value = app::types::VersionedValue{ req.value.value(), ts };
    }
    else if(req.operation == ExternalRequest::OperationType::Delete)
    {
        value = app::types::VersionedValue::tombstone(ts);
    }
    else
    {
        return ExternalResponseBuilder::from(
            ReplicationResult::makeFailure(
                error::AppError { 
                    error::AppErrorCode::InvalidRequest,
                    "Invalid operation type"
            })
        );
    }

    ReplicationPayload payload { req.key, value };

    return ExternalResponseBuilder::from(
        replicationOperation(payload, [&]() { return storage.set(payload.key, payload.value); })
    );    
}

cluster::protocol::InternalResponse ReplicationService::apply(const protocol::InternalRequest& req)
{
    auto validation = InternalValidator::validate<ReplicationPayload, InternalRequest::Type::Replication>(req);
    if(!validation.hasValue())
    {
        return InternalResponseBuilder::error(ReplicationErrorCode::InvalidRequest, validation.error().message);
    }

    const auto& payload = std::get<ReplicationPayload>(req.payload);

    auto applyResult = storage.set(payload.key, payload.value);
    if(!applyResult.hasValue())
    {
        return InternalResponseBuilder::error(ReplicationErrorCode::RemoteApplyFailed, applyResult.error().message);
    }
    return InternalResponseBuilder::from(ReplicationResponsePayload { true });
}

} // namespace app::cluster::services