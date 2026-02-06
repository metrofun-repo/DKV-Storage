#pragma once

#include <string>
#include <optional>

class KeyValueStorage;

class  KeyValueService
{
    KeyValueStorage& storage;
public:
    KeyValueService(KeyValueStorage& storage);

    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void remove(const std::string& key);
};