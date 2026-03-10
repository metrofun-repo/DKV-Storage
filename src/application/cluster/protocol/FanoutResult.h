#pragma once

#include <vector>
#include <string>

#include "common/utils/json_utils.h"
#include "error/ReplicationError.h"

namespace app::cluster::protocol {

struct FanoutResult
{
    using Json = common::json::json_t;

    struct NodeError
    {
        std::string node;
        error::ReplicationError error;
        NodeError(std::string id, error::ReplicationError e)
            : node(std::move(id))
            , error(e)
        {}
    };

    std::vector<std::string> acknowledged;
    std::vector<NodeError> failed;

    Json toJson() const
    {
        Json failedJson = Json::array();
        for(auto [node, error] : failed)
        {
            failedJson.push_back({
                { "node", node },
                { "error_code", error },
            });
        }
        Json ackedJson = Json::array();
        for(auto nodeId : acknowledged)
        {
            ackedJson.push_back(nodeId);
        }
        return {
            { "failed", failedJson },
            { "acked", ackedJson },
            { "received_acks", acknowledged.size() }
        };
    }
};

} // namespace app::api::cluster