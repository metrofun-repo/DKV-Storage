#pragma once

#include "JsonTraits.h"

#include "domain/replication/ReplicationResponsePayload.h"

namespace infra::serialization::traits {

// applied   : true/false
template <>
struct JsonTraits<domain::replication::ReplicationResponsePayload>
{
    using ReplicationResponsePayload = domain::replication::ReplicationResponsePayload;
    using Json                       = common::json::json_t;

    static Json toJson(const ReplicationResponsePayload& obj)
    {
        return {
            { "applied", obj.applied }
        };
    }

    static ParseResult<ReplicationResponsePayload> fromJson(const Json& json)
    {
        ReplicationResponsePayload obj;
        auto expApplied = common::json::getValue<bool>(json, "applied");
        if(!expApplied.hasValue())
        {
            return ParseResult<ReplicationResponsePayload>::makeFailure(expApplied.error());
        }

        return ParseResult<ReplicationResponsePayload>::makeSuccess(obj);
    }
};

} // namespace infra::serialization::traits