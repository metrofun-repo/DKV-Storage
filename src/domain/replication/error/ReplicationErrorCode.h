#pragma once

#include "common/utils/enum_utils.h"

namespace domain::replication::error {

enum class ReplicationErrorCode
{
    None = 0,
    InvalidRequest,
    NodeUnreachable,
    NodeTimeout,
    NodeInvalidResponse,
    RemoteApplyFailed,
    ClusterNotHealthy,
    QuorumNotReached,
    InternalError,
    Unknown
};

} // namespace domain::replication::error

namespace common::enum_utils {

template<>
struct EnumValues<domain::replication::error::ReplicationErrorCode>
{
    using Enum = domain::replication::error::ReplicationErrorCode;
    static inline constexpr std::array<Enum, 10> values =
    {
        Enum::None,
        Enum::InvalidRequest,
        Enum::NodeUnreachable,
        Enum::NodeTimeout,
        Enum::NodeInvalidResponse,
        Enum::RemoteApplyFailed,
        Enum::ClusterNotHealthy,
        Enum::QuorumNotReached,
        Enum::InternalError,
        Enum::Unknown
    };
};

} // namespace common::enum_utils