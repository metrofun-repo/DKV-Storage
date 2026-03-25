#pragma once
#include "JsonTraits.h"

#include "application/cluster/protocol/HeartbeatPayload.h"

namespace infra::serialization::traits {

template <>
struct JsonTraits<app::cluster::protocol::HeartbeatPayload>
{
    using HeartbeatPayload = app::cluster::protocol::HeartbeatPayload;
    using Json             = common::json::json_t;

    static Json toJson(const HeartbeatPayload& obj)
    {
        return {
            { "node", obj.nodeId },
            { "timestamp", obj.timestamp }
        };
    }

    static ParseResult<HeartbeatPayload> fromJson(const Json& json)
    {
        HeartbeatPayload obj;
        auto op = common::json::getValue<std::string>(json, "node");
        if(!op.hasValue())
        {
            return ParseResult<HeartbeatPayload>::makeFailure(op.error());
        }
        obj.nodeId = op.value();

        auto timestamp = common::json::getValue<int64_t>(json, "timestamp");
        if(!timestamp.hasValue())
        {
            return ParseResult<HeartbeatPayload>::makeFailure(timestamp.error());
        }
        obj.timestamp = timestamp.value();
        return ParseResult<HeartbeatPayload>::makeSuccess(obj);
    }
};

} // infra::serialization::traits