#pragma once

#include <string>
#include <optional>

#include "core/types/BasicResult.h"
#include "common/utils/json_utils.h"
#include "application/api/types/ClientOperationType.h"

namespace app::api::dto {

struct ClientRequest
{
    using Operation       = app::api::types::ClientOperationType;
    using JsonParseResult = core::types::BasicResult<ClientRequest>;
    using OpParseResult   = core::types::BasicResult<Operation>;
    using Json            = common::json::json_t;

    Operation operation;
    std::string key;
    std::optional<std::string> value;

    ClientRequest(
        Operation op = Operation::Unknown,
        std::string key = "",
        std::optional<std::string> value = std::nullopt
    );

    inline bool isReadRequest() const { return operation == Operation::Get; }

    Json toJson() const;
    static JsonParseResult fromJson(const Json & json);
    static OpParseResult parseOperation(const std::string& op);
    static std::optional<std::string> parseOperation(Operation op);
};

} // namespace app::api::dto