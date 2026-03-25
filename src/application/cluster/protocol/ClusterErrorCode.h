#pragma once

#include "common/utils/enum_utils.h"

namespace app::cluster::protocol {

enum class ClusterErrorCode
{
    None = 0,
    InvalidRequest,
    InternalError,
    Unknown
};

} // namespace app::cluster::protocol

namespace common::enum_utils {

template<>
struct EnumValues<app::cluster::protocol::ClusterErrorCode>
{
    using Enum = app::cluster::protocol::ClusterErrorCode;
    static inline constexpr std::array<Enum, 5> values =
    {
        Enum::None,
        Enum::InvalidRequest,
        Enum::InternalError,
        Enum::Unknown
    };
};

} // namespace common::enum_utils