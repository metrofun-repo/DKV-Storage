#include "ReplicationRequest.h"

namespace app::cluster::protocol {

ReplicationRequest::ReplicationRequest(
    Operation op,
    std::string key,
    std::optional<std::string> value, 
    uint64_t timestamp
)
    : operation(op)
    , key(std::move(key))
    , value(std::move(value))
    , timestamp(timestamp)
{}


ReplicationRequest::Json ReplicationRequest::toJson() const
{
    common::json::json_t json {
        { "key", key },
        { "timestamp", timestamp }
    };
    auto op = parseOperation(operation);
    json["op"] = op.value();
    if(value.has_value())
    {
        json["value"] = value;
    }
    return json;
}

ReplicationRequest::JsonParseResult ReplicationRequest::fromJson(const Json& json)
{
    ReplicationRequest req;
    auto op = common::json::getString(json, "op");
    if(!op.hasValue())
    {
        return JsonParseResult::makeFailure(op.error());
    }
    auto opStr = op.value();
    auto opCode = parseOperation(opStr);
    if(!opCode.hasValue())
    {
        return JsonParseResult::makeFailure(opCode.error());
    }
    req.operation = opCode.value();

    auto key = common::json::getString(json, "key");
    if(!key.hasValue())
    {
        return JsonParseResult::makeFailure(key.error());
    }
    req.key = key.value();

    auto value = common::json::getOptionalString(json, "value");
    if(!value.hasValue())
    {
        return JsonParseResult::makeFailure(value.error());
    }
    req.value = value.value();

    auto timestamp = common::json::getUnsigned(json, "timestamp");
    if(!timestamp.hasValue())
    {
        return JsonParseResult::makeFailure(timestamp.error());
    }
    req.timestamp = timestamp.value();
    return JsonParseResult::makeSuccess(req);
}

ReplicationRequest::OpParseResult ReplicationRequest::parseOperation(const std::string& op)
{
    static const std::unordered_map<std::string, Operation> table =
    {
        { "set"   , Operation::Set    },
        { "delete", Operation::Delete }
    };

    auto it = table.find(op); 
    if(it == table.end())
    {
        return OpParseResult::makeFailure("Invalid client operation: " + op);
    }
    return OpParseResult::makeSuccess(it->second);
}

std::optional<std::string> ReplicationRequest::parseOperation(Operation op)
{
    static const std::unordered_map<Operation, std::string> table =
    {
        { Operation::Set   , "set"    },
        { Operation::Delete, "delete" }
    };

    auto it = table.find(op); 
    if(it == table.end())
    {
        return std::nullopt;
    }
    return it->second;
}

} //namespace app::cluster::protocol