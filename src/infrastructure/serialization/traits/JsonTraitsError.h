#pragma once

#include "JsonTraits.h"
#include "core/types/Error.h"
#include "common/utils/enum_utils.h"

namespace infra::serialization::traits {

template <typename Enum>
struct JsonTraits<core::types::Error<Enum>>
{
    using Error = core::types::Error<Enum>;
    using Json  = common::json::json_t;

    static Json toJson(const Error& obj)
    {
        return {
            { "code"   , static_cast<uint32_t>(obj.code) },
            { "message", obj.message },
        };
    }
    static ParseResult<Error> fromJson(const Json& json)
    {
        auto enumInt = common::json::getValue<uint32_t>(json, "code");
        if(!enumInt.hasValue())
        {
            return ParseResult<Error>::makeFailure(enumInt.error());
        }
        auto enumValue = common::enum_utils::safeEnumCast<Enum>(enumInt.value());
        if(!enumValue.hasValue())
        {
            return ParseResult<Error>::makeFailure(enumValue.error());
        }

        auto message = common::json::getValue<std::string>(json, "message");
        if(!message.hasValue())
        {
            return ParseResult<Error>::makeFailure(message.error());
        }
    
        return ParseResult<Error>::makeSuccess(Error {
            enumValue.value(),
            message.value()
        });
    }
};

} // namespace infra::serialization::traits