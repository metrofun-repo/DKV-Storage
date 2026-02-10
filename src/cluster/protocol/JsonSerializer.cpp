#include "JsonSerializer.h"

nlohmann::json toJson(ReplicationMessage msg)
{
    nlohmann::json json {
        { "op", msg.operation },
        { "key", msg.key },
        { "timestamp", msg.timestamp }
    };
    if(msg.value.has_value())
    {
        json["value"] = msg.value;
    }
    return json;
}
ReplicationMessage fromJson(const nlohmann::json& json)
{
    ReplicationMessage msg;
    if(!json.contains("op"))
    {
        throw std::runtime_error("Failed to parse json for ReplicationMessage: missing 'op'");
    }
    msg.operation = json["op"];

    if(!json.contains("key"))
    {
        throw std::runtime_error("Failed to parse json for ReplicationMessage: missing 'key'");
    }
    msg.key = json["key"];

    if(!json.contains("timestamp"))
    {
        throw std::runtime_error("Failed to parse json for ReplicationMessage: missing 'timestamp'");
    }
    msg.timestamp = json["timestamp"];

    if(json.contains("value"))
    {
        msg.value = json["value"];
    }
    return msg;
}
