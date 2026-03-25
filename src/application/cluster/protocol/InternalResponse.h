#pragma once

#include <variant>
#include <optional>

#include "ClusterError.h"
#include "domain/replication/HeartbeatResponsePayload.h"
#include "domain/replication/ReplicationResponsePayload.h"


namespace app::cluster::protocol {

struct InternalResponse
{
    using HeartbeatResponsePayload   = domain::replication::HeartbeatResponsePayload;
    using ReplicationResponsePayload = domain::replication::ReplicationResponsePayload;

    enum class Type
    {
        Invalid,
        Heartbeat,
        Replication
    };

    Type type;
    std::variant<HeartbeatResponsePayload, ReplicationResponsePayload> payload;
    std::optional<app::cluster::protocol::ClusterError> error;
};

} // namespace app::cluster::protocol

namespace common::enum_utils {

template<>
struct EnumValues<app::cluster::protocol::InternalResponse::Type>
{
    using Enum = app::cluster::protocol::InternalResponse::Type;
    static inline constexpr std::array<Enum, 3> values =
    {
        Enum::Invalid,
        Enum::Heartbeat,
        Enum::Replication
    };
};

} // namespace common::enum_utils