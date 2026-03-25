#pragma once

#include "JsonTraitsError.h"
#include "JsonTraitsHeartbeatResponsePayload.h"
#include "JsonTraitsReplicationResponsePayload.h"
#include "application/cluster/protocol/InternalResponse.h"

namespace infra::serialization::traits {

template <>
struct JsonTraits<app::cluster::protocol::InternalResponse>
{
    using InternalResponse = app::cluster::protocol::InternalResponse;
    using Error            = app::cluster::protocol::ClusterError;

    using HbResponse = domain::replication::HeartbeatResponsePayload;
    using RpResponse = domain::replication::ReplicationResponsePayload;
    
    using Json = common::json::json_t;

    static Json toJson(const InternalResponse& obj)
    {
        Json json {
            { "type"   , static_cast<uint32_t>(obj.type) }
        };

        Json payload;

        std::visit([&](auto&& inner)
        {
            using InnerT = std::decay_t<decltype(inner)>;
            payload = JsonTraits<InnerT>::toJson(inner);
        }, obj.payload);

        json["payload"] = payload;

        if(obj.error.has_value())
        {
            json["error"] = JsonTraits<Error>::toJson(obj.error.value());
        }

        return json;
    }

    static ParseResult<InternalResponse> fromJson(const Json& json)
    {
        InternalResponse obj;
        auto type = common::json::getValue<uint32_t>(json, "type");
        if(!type.hasValue())
        {
            return ParseResult<InternalResponse>::makeFailure(type.error());
        }

        auto typeCast = common::enum_utils::safeEnumCast<InternalResponse::Type>(type.value());
        if(!typeCast.hasValue())
        {
            return ParseResult<InternalResponse>::makeFailure(typeCast.error());
        }
        obj.type = typeCast.value();

        auto payload = common::json::getValue<Json>(json, "payload");
        if(!payload.hasValue())
        {
            return ParseResult<InternalResponse>::makeFailure(payload.error());
        }

        switch(obj.type)
        {
            case InternalResponse::InternalResponse::Type::Heartbeat :
            {
                auto hb = JsonTraits<HbResponse>::fromJson(payload.value());
                if(!hb.hasValue())
                {
                    return ParseResult<InternalResponse>::makeFailure(hb.error());
                }
                obj.payload = hb.value();
                break;
            }
            case InternalResponse::InternalResponse::Type::Replication :
            {
                auto rp = JsonTraits<RpResponse>::fromJson(payload.value());
                if(!rp.hasValue())
                {
                    return ParseResult<InternalResponse>::makeFailure(rp.error());
                }
                obj.payload = rp.value();
                break;
            }
        }

        auto errorOpt = common::json::getOptionalValue<Json>(json, "error");
        if(!errorOpt.hasValue())
        {
            return ParseResult<InternalResponse>::makeFailure(errorOpt.error());
        }
    
        auto errorJson = errorOpt.value();
        if(errorJson.has_value())
        {
            auto error = JsonTraits<Error>::fromJson(errorJson.value());
            if(!error.hasValue())
            {
                return ParseResult<InternalResponse>::makeFailure(error.error().message);
            }
            obj.error = error.value();
        }

        return ParseResult<InternalResponse>::makeSuccess(obj);
    }
};

} // namespace infra::serialization::traits