#pragma once

#include <variant>

#include "HeartbeatPayload.h"
#include "ReplicationPayload.h"
#include "common/utils/enum_utils.h"

namespace app::cluster::protocol {

struct InternalRequest
{
    enum class Type
    {
        Heartbeat,
        Replication
    };
    Type type;
    std::variant<HeartbeatPayload, ReplicationPayload> payload;
};

} // namespace app::cluster::protocol

namespace common::enum_utils {

template<>
struct EnumValues<app::cluster::protocol::InternalRequest::Type>
{
    using Enum = app::cluster::protocol::InternalRequest::Type;
    static inline constexpr std::array<Enum, 2> values =
    {
        Enum::Heartbeat,
        Enum::Replication
    };
};

} // namespace common::enum_utils