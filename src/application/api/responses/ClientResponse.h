#pragma once

#include <string>
#include "core/types/BasicResult.h"
#include "common/utils/json_utils.h"

namespace app::api::dto {

struct ClientResponse
{
    using Result = core::types::BasicResult<ClientResponse>;
    using Json = common::json::json_t;

    bool success;
    std::string status;
    std::string message;
    Json data;

    Json toJson() const;
    static Result fromJson(const Json& json);
};

} // namespace app::api::dto