#pragma once

#include <string>
#include "common/utils/json_utils.h"
#include "error/ReplicationError.h"

// json response structure
// {
//   applied   : true/false
//   error_code: uint
// }

namespace app::cluster::types {

struct  ReplicationApplyResult 
{
    using ReplicationError = error::ReplicationError;

    using JsonParseResult  = core::types::BasicResult<ReplicationApplyResult>;
    using ErrorParseResult = core::types::BasicResult<ReplicationError>;

    using Json = common::json::json_t;

    bool applied;
    ReplicationError error;

    ReplicationApplyResult(bool ok = true, ReplicationError code = ReplicationError::None);

    Json toJson() const;
    static ErrorParseResult parseError(uint64_t error);
    static JsonParseResult fromJson(const Json& json);
};

} // namespace app::cluster::types