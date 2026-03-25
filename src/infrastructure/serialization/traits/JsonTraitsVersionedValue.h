#pragma once
#include "JsonTraits.h"
#include "application/types/KeyValueTypes.h"

namespace infra::serialization::traits {

template <>
struct JsonTraits<app::types::VersionedValue>
{
    using VersionedValue = app::types::VersionedValue;
    using Json           = common::json::json_t;

    static Json toJson(const VersionedValue& obj)
    {
        Json json;
        json["ts"] = obj.timestamp;

        if(!obj.isTombstone())
        {
            json["value"] = std::get<app::types::Value>(obj.value);
        }
        return json;
    }

    static ParseResult<VersionedValue> fromJson(const Json& json)
    {
        auto timestamp = common::json::getValue<int64_t>(json, "ts");
        if(!timestamp.hasValue())
        {
            return ParseResult<VersionedValue>::makeFailure(timestamp.error());
        }

        auto valueOpt = common::json::getOptionalValue<app::types::Value>(json, "value");
        if(!valueOpt.hasValue())
        {
            return ParseResult<VersionedValue>::makeFailure(valueOpt.error());
        }
        const auto& value = valueOpt.value();
        if(!value.has_value())
        {
            ParseResult<VersionedValue>::makeSuccess(VersionedValue::tombstone(timestamp.value()));
        }

        return ParseResult<VersionedValue>::makeSuccess(VersionedValue { value.value(), timestamp.value() });
    }
};

} // namespace infra::serialization::traits