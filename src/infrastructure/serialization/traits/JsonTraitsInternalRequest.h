#pragma once

#include "JsonTraits.h"
#include "JsonTraitsHeartbeatRequest.h"
#include "JsonTraitsReplicationPayload.h"
#include "application/cluster/protocol/InternalRequest.h"


namespace infra::serialization::traits {

template <>
struct JsonTraits<app::cluster::protocol::InternalRequest>
{
    using InternalRequest = app::cluster::protocol::InternalRequest;
    using HbRequest       = app::cluster::protocol::HeartbeatPayload;
    using RpRequest       = app::cluster::protocol::ReplicationPayload;

    using Json            = common::json::json_t;

    static Json toJson(const InternalRequest& obj)
    {
        Json payload;

        std::visit([&](auto&& inner)
        {
            using InnerT = std::decay_t<decltype(inner)>;
            payload = JsonTraits<InnerT>::toJson(inner);
        }, obj.payload);

        return {
            { "type", static_cast<uint32_t>(obj.type) },
            { "payload" , payload }
        };
    }

    static ParseResult<InternalRequest> fromJson(const Json& json)
    {
        InternalRequest obj;
        auto type = common::json::getValue<uint32_t>(json, "type");
        if(!type.hasValue())
        {
            return ParseResult<InternalRequest>::makeFailure(type.error());
        }
        auto typeCast = common::enum_utils::safeEnumCast<InternalRequest::Type>(type.value());
        if(!typeCast.hasValue())
        {
            return ParseResult<InternalRequest>::makeFailure(typeCast.error());
        }
        obj.type = typeCast.value();

        auto payload = common::json::getValue<Json>(json, "payload");
        if(!payload.hasValue())
        {
            return ParseResult<InternalRequest>::makeFailure(payload.error());
        }

        switch(obj.type)
        {
            case InternalRequest::Type::Heartbeat :
            {
                auto hb = JsonTraits<HbRequest>::fromJson(payload.value());
                if(!hb.hasValue())
                {
                    return ParseResult<InternalRequest>::makeFailure(hb.error());
                }
                obj.payload = hb.value();
                break;
            }
            case InternalRequest::Type::Replication :
            {
                auto rp = JsonTraits<RpRequest>::fromJson(payload.value());
                if(!rp.hasValue())
                {
                    return ParseResult<InternalRequest>::makeFailure(rp.error());
                }
                obj.payload = rp.value();
                break;
            }
            default: return ParseResult<InternalRequest>::makeFailure("Invalid cluster request type");
        }

        return ParseResult<InternalRequest>::makeSuccess(obj);
    }
};

} // infra::serialization::traits