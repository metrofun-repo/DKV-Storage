#include "KeyValueStorage.h"

void KeyValueStorage::put(const std::string& key, const std::string& value, uint64_t timestamp)
{
    if(auto it = map.find(key); it == map.end() || it->second.timestamp < timestamp)
    {
        map[key] = { value, timestamp };
    }
}

std::optional<ValueWithTimestamp> KeyValueStorage::get(const std::string& key) const
{
    if(auto it = map.find(key); it != map.end())
    {
        return it->second;
    }
    return std::nullopt;
}

void KeyValueStorage::remove(const std::string& key)
{
    if(auto it = map.find(key); it != map.end())
    {
        map.erase(it);
    }
}