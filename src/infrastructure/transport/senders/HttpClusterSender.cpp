#include "HttpClusterSender.h"

#include "infrastructure/http/routing/Routes.h"
#include "infrastructure/http/client/HttpClientResponsePayload.h"

#include "infrastructure/transport/error/TransportErrorCode.h"
#include "infrastructure/serialization/JsonSerializer.h"
#include "infrastructure/serialization/traits/JsonTraitsInternalRequest.h"
#include "infrastructure/serialization/traits/JsonTraitsInternalResponse.h"

namespace infra::transport::senders {

using HttpClientResponsePayload = http::client::HttpClientResponsePayload;
using HttpClientErrorCode       = http::client::HttpClientErrorCode;
using JsonSerializer            = serialization::JsonSerializer;
using InternalRequest   = app::cluster::protocol::InternalRequest;
using InternalResponse  = app::cluster::protocol::InternalResponse;
using NodeInfo          = domain::cluster::model::NodeInfo;

HttpClusterSender::HttpClusterSender(http::client::HttpClient& client)
    : httpClient(client)
{}

HttpClusterSender::TransportSendResult HttpClusterSender::send(const InternalRequest& req, const NodeInfo& node) const
{
        auto data = JsonSerializer::serialize(req);
        auto endpoint = http::routing::routes::INTERNAL;

        const auto& [nodeId, host, port] = node;
        auto clientResult = httpClient.post(host, port, endpoint,  reinterpret_cast<const char*>(data.bytes.data()), data.bytes.size(), data.contentType);
        if(!clientResult.hasValue())
        {
            return TransportSendResult::makeFailure(mapHttpToTransportError(clientResult.error().code));
        }    

        HttpClientResponsePayload clientResponse = clientResult.value();
        if(clientResponse.status < 200 || clientResponse.status >= 300)
        {
            return TransportSendResult::makeFailure(mapHttpStatusToTransportError(clientResponse.status));
        }

        auto response = JsonSerializer::deserialize<InternalResponse>(clientResponse.body);

        if(!response.hasValue())
        {
            //return TransportSendResult::makeFailure(TransportError { TransportErrorCode::DeserializationFailed, 0 });
            return TransportSendResult::makeFailure(error::TransportError { error::TransportErrorCode::InvalidResponse, 0 });
        }

        return TransportSendResult::makeSuccess(response.value());
}

error::TransportError HttpClusterSender::mapHttpToTransportError(HttpClientErrorCode code) const
{
    switch(code)
    {
        case HttpClientErrorCode::Connection : return { error::TransportErrorCode::ConnectionRefused, "Connection refused" };
        case HttpClientErrorCode::Read       : 
        case HttpClientErrorCode::Write      : return { error::TransportErrorCode::HostUnreachable, "Host unreachable" };
        case HttpClientErrorCode::Timeout    : return { error::TransportErrorCode::Timeout, "Timeout" };
        default                              : return { error::TransportErrorCode::Unknown, "Unknown transport error" };
    }
}

error::TransportError HttpClusterSender::mapHttpStatusToTransportError(int status) const
{
    if(status >= 500)
    {
        return { error::TransportErrorCode::HostUnreachable, std::to_string(status) };
    }

    if(status >= 400)
    {
        return { error::TransportErrorCode::HttpError, std::to_string(status) };
    }

    return { error::TransportErrorCode::Unknown, std::to_string(status) };
}

}