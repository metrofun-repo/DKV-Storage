#pragma once

#include <string>
#include <optional>
#include <unordered_map>

struct ValueWithTimestamp
{
    std::string value;
    uint64_t timestamp;
    ValueWithTimestamp() = default;
};

class KeyValueStorage
{
    std::unordered_map<std::string, ValueWithTimestamp> map;
public:
    void put(const std::string& key, const std::string& value, uint64_t timestamp);

    std::optional<ValueWithTimestamp> get(const std::string& key) const;

    void remove(const std::string& key);
};