#pragma once

#include "JsonTraitsError.h"
#include "JsonTraitsNodeError.h"
#include "domain/replication/FanoutResult.h"

namespace infra::serialization::traits {

template <typename ErrorT>
struct JsonTraits<domain::replication::FanoutResult<ErrorT>>
{
    using FanoutResult = domain::replication::FanoutResult<ErrorT>;
    using NodeError    = domain::replication::error::NodeError<ErrorT>;
    using Json         = common::json::json_t;

    static Json toJson(const FanoutResult& obj)
    {
        Json failedJson = Json::array();
        for(auto error : obj.failed)
        {
            failedJson.push_back(JsonTraits<NodeError>::toJson(error));
            // failedJson.push_back({
            //     { "node", node },
            //     { "error_code", static_cast<uint32_t>(error) },
            // });
        }
        Json ackedJson = Json::array();
        for(auto nodeId : obj.acknowledged)
        {
            ackedJson.push_back(nodeId);
        }
        return {
            { "failed", failedJson },
            { "acked", ackedJson },
            { "received_acks", obj.acknowledged.size() }
        };
    }

    static ParseResult<FanoutResult> fromJson(const Json& json)
    {
        //TODO
        return ParseResult<FanoutResult>::makeSuccess(FanoutResult());
    }
};

} // namespace infra::serialization::traits