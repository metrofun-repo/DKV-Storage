#pragma once

#include "common/utils/json_utils.h"
#include "application/api/types/ReplicationOperationType.h"

// json structure
// {
//   "op"         : operation,
//   "key"        : key,
//   "value" : value.value()
//   "timestamp"  : timestamp
// }
namespace app::cluster::protocol {

struct ReplicationRequest
{
    using Operation       = app::api::types::ReplicationOperationType;
    using JsonParseResult = core::types::BasicResult<ReplicationRequest>;
    using OpParseResult   = core::types::BasicResult<Operation>;
    using Json            = common::json::json_t;

    Operation operation;
    std::string key;
    std::optional<std::string> value;
    uint64_t timestamp;
    
    ReplicationRequest(
        Operation op = Operation::Unknown,
        std::string key = "",
        std::optional<std::string> value = std::nullopt,
        uint64_t timestamp = 0
    );

    Json toJson() const;
    static JsonParseResult fromJson(const Json& json);
    static OpParseResult parseOperation(const std::string& op);
    static std::optional<std::string> parseOperation(Operation op);
};

} // namespace app::cluster::protocol