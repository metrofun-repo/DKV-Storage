#pragma once

#include <array>
#include <string>
#include "core/types/BasicResult.h"

namespace common::enum_utils {

template <typename Enum>
struct EnumValues;

template <typename Enum>
core::types::BasicResult<Enum> safeEnumCast(uint32_t value)
{
    for(Enum e : EnumValues<Enum>::values)
    {
        if(static_cast<uint32_t>(e) == value)
        {
            return core::types::BasicResult<Enum>::makeSuccess(e);
        }
    }
    return core::types::BasicResult<Enum>::makeFailure("Invalid enum value " + std::to_string(value));
}

} // namespace common::enum_utils