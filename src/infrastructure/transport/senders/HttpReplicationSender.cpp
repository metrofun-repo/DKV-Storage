#include "HttpReplicationSender.h"

#include <iostream>
#include "common/utils/json_utils.h"
#include "infrastructure/http/routing/Routes.h"
#include "infrastructure/http/client/HttpClientResponsePayload.h"

#include "application/cluster/types/ReplicationApplyResult.h"

namespace infra::transport::senders {

using infra::http::client::HttpClientResponsePayload;
using infra::transport::error::TransportErrorCode;

using ReplicationApplyResult = app::cluster::types::ReplicationApplyResult;

HttpReplicationSender::HttpReplicationSender(HttpClient& client)
    : httpClient(client)
{}

HttpReplicationSender::TransportError HttpReplicationSender::mapHttpToTransportError(HttpClientErrorCode code) const
{
    switch(code)
    {
        case HttpClientErrorCode::Connection : return { TransportErrorCode::ConnectionRefused, 0 };
        case HttpClientErrorCode::Read       : 
        case HttpClientErrorCode::Write      : return { TransportErrorCode::HostUnreachable, 0 };
        case HttpClientErrorCode::Timeout    : return { TransportErrorCode::Timeout, 0 };
        default                              : return { TransportErrorCode::Unknown, 0 };
    }
}

HttpReplicationSender::TransportError HttpReplicationSender::mapHttpStatusToTransportError(int status) const
{
    if(status >= 500)
    {
        return { TransportErrorCode::HostUnreachable, status };
    }

    if(status >= 400)
    {
        return { TransportErrorCode::HttpError, status };
    }

    return { TransportErrorCode::Unknown, status };
}

HttpReplicationSender::TransportSendResult HttpReplicationSender::send(const ReplicationRequest& req, const NodeInfo& node) const
{
    auto reqJson = req.toJson();
    const auto& [nodeId, host, port] = node;
    const std::string body = reqJson.dump();

    std::cout << "replica body: " << body << std::endl;
    auto clientResult = httpClient.post(host, port, infra::http::routing::routes::REPLICATE, body, "application/json");

    if(!clientResult.hasValue())
    {
        return TransportSendResult::makeFailure(mapHttpToTransportError(clientResult.error().code));
    }    

    HttpClientResponsePayload clientResponse = clientResult.value();

    if(clientResponse.status < 200 || clientResponse.status >= 300)
    {
        return TransportSendResult::makeFailure(mapHttpStatusToTransportError(clientResponse.status));
    }

    auto json = common::json::parse(clientResponse.body);
    if(!json.hasValue())
    {
        return TransportSendResult::makeFailure(TransportError { TransportErrorCode::DeserializationFailed, 0 });
    }

    auto replicaRespose = ReplicationApplyResult::fromJson(json.value());
    if(!replicaRespose.hasValue())
    {
        return TransportSendResult::makeFailure(TransportError { TransportErrorCode::InvalidResponse, 0 });
    }

    return TransportSendResult::makeSuccess();
}

} // namespace infra::transport::senders