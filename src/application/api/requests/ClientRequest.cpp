#include "ClientRequest.h"

namespace app::api::dto {

ClientRequest::ClientRequest(
    Operation op,
    std::string key,
    std::optional<std::string> value
)
    : operation(op)
    , key(std::move(key))
    , value(std::move(value))
{}

ClientRequest::Json ClientRequest::toJson() const
{
    //TODO
    return {};
}

ClientRequest::JsonParseResult ClientRequest::fromJson(const nlohmann::json & json)
{
    ClientRequest req;
    auto expOpStr = common::json::getString(json, "op");
    if(!expOpStr.hasValue())
    {
        return JsonParseResult::makeFailure(expOpStr.error());
    }
    
    auto expOp = parseOperation(expOpStr.value());
    if(!expOp.hasValue())
    {
        return JsonParseResult::makeFailure(expOp.error());
    }
    req.operation = expOp.value();

    auto expKeyStr = common::json::getString(json, "key");
    if(!expKeyStr.hasValue())
    {
        return JsonParseResult::makeFailure(expKeyStr.error());
    }
    req.key = expKeyStr.value();

    auto expOptStr = common::json::getOptionalString(json, "value");
    if(!expOptStr.hasValue())
    {
        return JsonParseResult::makeFailure(expOptStr.error());
    }
    req.value = expOptStr.value();
    return JsonParseResult::makeSuccess(req);
}

ClientRequest::OpParseResult ClientRequest::parseOperation(const std::string& op)
{
    static const std::unordered_map<std::string, Operation> table =
    {
        { "get", Operation::Get },
        { "set", Operation::Set },
        { "delete", Operation::Delete }
    };

    auto it = table.find(op); 
    if(it == table.end())
    {
        return OpParseResult::makeFailure("Invalid client operation: " + op);
    }
    return OpParseResult::makeSuccess(it->second);
}

std::optional<std::string> ClientRequest::parseOperation(Operation op)
{
    static const std::unordered_map<Operation, std::string> table =
    {
        { Operation::Get, "get" },
        { Operation::Set, "set" },
        { Operation::Delete, "delete" }
    };

    auto it = table.find(op); 
    if(it == table.end())
    {
        return std::nullopt;
    }
    return it->second;
}

} // namespace app::api::dto