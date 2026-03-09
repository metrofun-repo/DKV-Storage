#include "ReplicatorService.h"

#include <chrono>
#include "application/api/validation/ClientRequestValidator.h"

namespace app::cluster::services {

using StorageError = error::StorageError;
using app::api::validation::ClientRequestValidator;

ReplicatorService::ReplicatorService(StorageService& service, ReplicationSender& repSend, const NodeInfo& self, const std::vector<NodeInfo>& nodes)
    : domain(service)
    , sender(repSend)
    , selfNode(self)
    , clusterNodes(nodes)
{}

ReplicatorService::ReplicationError ReplicatorService::fromTransport(TransportErrorCode code) const
{
    switch(code)
    {
        case TransportErrorCode::Timeout : return ReplicationError::NodeTimeout; 

        
        case TransportErrorCode::HttpError         :  
        case TransportErrorCode::HostUnreachable   :  
        case TransportErrorCode::ConnectionRefused : return ReplicationError::NodeUnreachable; 

        case TransportErrorCode::InvalidResponse : return ReplicationError::NodeInvalidResponse;

        case TransportErrorCode::SerializationFailed   : 
        case TransportErrorCode::DeserializationFailed : return ReplicationError::InternalError;

        default : return error::ReplicationError::Unknown;
    }
}

ReplicatorService::FanoutResult ReplicatorService::fanout(const ReplicationRequest& req) const
{
    FanoutResult result;

    for(auto& node : clusterNodes)
    {
        auto res = sender.send(req, node);
        
        if(!res.hasValue())
        {
            result.failed.emplace_back(node.nodeId, fromTransport(res.error().code));
            continue;
        }
        result.acknowledged.emplace_back(node.nodeId);
    }
    return result;
}

ReplicatorService::ReplicationResult ReplicatorService::quorumReached(const FanoutResult& fanout) const
{
    const size_t totalNodes = clusterNodes.size() + 1;
    const size_t quorum = (totalNodes / 2) + 1;
    const size_t acks = fanout.acknowledged.size() + 1;

    if(acks < quorum)
    {
        return ReplicationResult::makeFailure(ReplicationError::QuorumNotReached, fanout);
    }

    return ReplicationResult::makeSuccess(fanout);
}

ReplicatorService::ReplicationResult ReplicatorService::set(const ClientRequest& req)
{
    auto valid = ClientRequestValidator::validate(req);
    if(!valid.hasValue())
    {
        return ReplicationResult::makeFailure(ReplicationError::InvalidRequest, {});
    }

    const uint64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    auto localApply = domain.set(req.key, req.value.value(), timestamp);
    if(!localApply.hasValue())
    {
        return ReplicationResult::makeFailure(localApply.error());//ReplicationError::LocalApplyFailed
    }

    ReplicationRequest request { ReplicationRequest::Operation::Set, req.key, req.value.value(), timestamp };

    return quorumReached(fanout(request));
}

ReplicatorService::ReplicationResult ReplicatorService::remove(const ClientRequest& req)
{
    auto valid = ClientRequestValidator::validate(req);
    if(!valid.hasValue())
    {
        return ReplicationResult::makeFailure(ReplicationError::InvalidRequest, {});
    }

    auto localApply = domain.remove(req.key);
    if(!localApply.hasValue())
    {
        return ReplicationResult::makeFailure(localApply.error()); //ReplicationError::LocalApplyFailed
    }

    ReplicationRequest request{ ReplicationRequest::Operation::Delete, req.key };
    return quorumReached(fanout(request));
}

} // namespace app::cluster::services