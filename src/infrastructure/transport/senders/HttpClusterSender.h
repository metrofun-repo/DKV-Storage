#pragma once

#include <cstddef>

#include "domain/cluster/model/NodeInfo.h"

#include "infrastructure/http/client/HttpClient.h"
#include "infrastructure/http/client/HttpClientError.h"
#include "infrastructure/transport/error/TransportError.h"

#include "application/cluster/protocol/InternalRequest.h"
#include "application/cluster/protocol/InternalResponse.h"


namespace infra::transport::senders {


class HttpClusterSender
{   
public:
    using TransportSendResult  = core::types::Expected<app::cluster::protocol::InternalResponse, error::TransportError>;

    explicit HttpClusterSender(http::client::HttpClient& client);

    TransportSendResult send(
        const app::cluster::protocol::InternalRequest& req,
        const domain::cluster::model::NodeInfo& node) const;

private:
    error::TransportError mapHttpToTransportError(http::client::HttpClientErrorCode code) const;
    error::TransportError mapHttpStatusToTransportError(int status) const;

    http::client::HttpClient& httpClient;
};

} // namespace infra::transport::senders