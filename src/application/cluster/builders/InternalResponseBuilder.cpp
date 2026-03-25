#include "InternalResponseBuilder.h"

namespace app::cluster::builders {

using InternalResponse = protocol::InternalResponse;
using ReplicationResponsePayload = domain::replication::ReplicationResponsePayload;
using ReplicationError           = domain::replication::error::ReplicationError;
using ReplicationErrorCode       = domain::replication::error::ReplicationErrorCode;

InternalResponse InternalResponseBuilder::from(const ReplicationResponsePayload& payload)
{
    return InternalResponse { InternalResponse::Type::Replication, payload };
}

InternalResponse InternalResponseBuilder::from(const domain::replication::HeartbeatResponsePayload& payload)
{
    return InternalResponse { InternalResponse::Type::Heartbeat, payload };
}

InternalResponse InternalResponseBuilder::error(ReplicationErrorCode code, const std::string& msg)
{
    return from(ReplicationResponsePayload { false, ReplicationError { code, msg } });
}

} // namespace app::api::builders