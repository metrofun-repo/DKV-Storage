#pragma once

#include <string>
#include "common/utils/json_utils.h"

namespace app::api::dto {

struct ExternalResponse
{
    using Json = common::json::json_t;

    bool success;
    std::string status;
    std::string message;
    Json data;
};

} // namespace app::api::dto