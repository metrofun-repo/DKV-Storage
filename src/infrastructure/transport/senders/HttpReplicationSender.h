#pragma once

#include <vector>

#include "ReplicationSender.h"
#include "domain/cluster/model/NodeInfo.h"
#include "infrastructure/http/client/HttpClient.h"
#include "infrastructure/http/client/HttpClientError.h"
#include "infrastructure/transport/error/TransportError.h"
#include "application/cluster/protocol/ReplicationRequest.h"

namespace infra::transport::senders {

class HttpReplicationSender : public ReplicationSender
{

    using HttpClient          = infra::http::client::HttpClient;
    using HttpClientErrorCode = infra::http::client::HttpClientErrorCode;

    using ReplicationRequest  = ReplicationSender::ReplicationRequest;
    using NodeInfo            = ReplicationSender::NodeInfo;
    using TransportError      = ReplicationSender::TransportError;
    using TransportSendResult = ReplicationSender::TransportSendResult;

public:
    explicit HttpReplicationSender(HttpClient& client);

    TransportSendResult send(const ReplicationRequest& req, const NodeInfo& node) const override;

private:
    TransportError mapHttpToTransportError(HttpClientErrorCode code) const;
    TransportError mapHttpStatusToTransportError(int status) const;

    HttpClient& httpClient;
};

} // namespace infra::transport::senders