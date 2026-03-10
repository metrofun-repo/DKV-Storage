#pragma once

#include "infrastructure/transport/error/TransportError.h"
#include "infrastructure/transport/senders/ReplicationSender.h"
#include "application/cluster/protocol/ReplicationRequest.h"
class MockReplicationSender : public infra::transport::senders::ReplicationSender
{
    using Result = core::types::Expected<void, TransportError>;
public:
    mutable std::string body;
    Result send(const ReplicationRequest& req, const NodeInfo& node) const
    {
        body.assign(req.toJson().dump());
        return Result::makeSuccess();
    }
};