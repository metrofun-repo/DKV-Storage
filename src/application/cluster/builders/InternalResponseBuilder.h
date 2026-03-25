#pragma once

#include "domain/replication/ReplicationResponsePayload.h"
#include "application/cluster/protocol/InternalResponse.h"

namespace app::cluster::builders {

struct InternalResponseBuilder
{
    static protocol::InternalResponse from(const domain::replication::ReplicationResponsePayload& payload);
    static protocol::InternalResponse from(const domain::replication::HeartbeatResponsePayload& payload);
    static protocol::InternalResponse error(domain::replication::error::ReplicationErrorCode code, const std::string& msg);
};

} // namespace app::api::builders