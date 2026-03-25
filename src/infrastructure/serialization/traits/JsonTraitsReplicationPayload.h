#pragma once

#include <optional>
#include "common/utils/enum_utils.h"
#include "application/cluster/protocol/ReplicationPayload.h"
#include "JsonTraitsVersionedValue.h"

namespace infra::serialization::traits {

//             "key" : key,
// "versioned_value" : { [opt]value, ts }
template <>
struct JsonTraits<app::cluster::protocol::ReplicationPayload>
{
    using ReplicationPayload = app::cluster::protocol::ReplicationPayload;
    using Json               = common::json::json_t;

    static Json toJson(const ReplicationPayload& obj)
    {
        Json json {
            { "key", obj.key },
            { "versioned_value", JsonTraits<app::types::VersionedValue>::toJson(obj.value) }
        };
        return json;
    }

    static ParseResult<ReplicationPayload> fromJson(const Json& json)
    {
        ReplicationPayload obj;

        auto key = common::json::getValue<std::string>(json, "key");
        if(!key.hasValue())
        {
            return ParseResult<ReplicationPayload>::makeFailure(key.error());
        }
        obj.key = key.value();

        auto valueJson = common::json::getValue<Json>(json, "versioned_value");
        if(!valueJson.hasValue())
        {
            return ParseResult<ReplicationPayload>::makeFailure(valueJson.error());
        }

        auto value = JsonTraits<app::types::VersionedValue>::fromJson(valueJson.value());
        if(!value.hasValue())
        {
            return ParseResult<ReplicationPayload>::makeFailure(value.error());
        }
        
        obj.value = value.value();

        return ParseResult<ReplicationPayload>::makeSuccess(obj);
    }
};

} // namespace infra::serialization::traits