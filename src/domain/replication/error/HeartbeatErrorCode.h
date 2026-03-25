#pragma once

#include "common/utils/enum_utils.h"

namespace domain::replication::error {

enum class HeartbeatErrorCode
{
    None = 0,
    ApplyFailed,
    Unknown
};

} // namespace domain::replication::error

namespace common::enum_utils {

template<>
struct EnumValues<domain::replication::error::HeartbeatErrorCode>
{
    using Enum = domain::replication::error::HeartbeatErrorCode;
    static inline constexpr std::array<Enum, 3> values =
    {
        Enum::None,
        Enum::ApplyFailed,
        Enum::Unknown
    };
};

} // namespace common::enum_utils