#pragma once

#include "JsonTraits.h"
#include "domain/replication/HeartbeatResponsePayload.h"

namespace infra::serialization::traits {

template <>
struct JsonTraits<domain::replication::HeartbeatResponsePayload>
{
    using HeartbeatResponsePayload = domain::replication::HeartbeatResponsePayload;
    using Json                     = common::json::json_t;

    static Json toJson(const HeartbeatResponsePayload& obj)
    {
        return {
            { "applied", obj.applied }
        };
    }
    static ParseResult<HeartbeatResponsePayload> fromJson(const Json& json)
    {
        HeartbeatResponsePayload obj;
        auto applied = common::json::getValue<bool>(json, "applied");
        if(!applied.hasValue())
        {
            return ParseResult<HeartbeatResponsePayload>::makeFailure(applied.error());
        }
        obj.applied = applied.value();
        return ParseResult<HeartbeatResponsePayload>::makeSuccess(obj);
    }
};

} // infra::serialization::traits