#include "KeyValueService.h"

#include "store/KeyValueStorage.h"

#include <chrono>

KeyValueService::KeyValueService(KeyValueStorage& storage)
    : storage(storage)
{
}

void KeyValueService::set(const std::string& key, const std::string& value)
{
    storage.put(key, value, std::chrono::steady_clock::now().time_since_epoch().count());
}

std::optional<std::string> KeyValueService::get(const std::string& key)
{
    auto val = storage.get(key);
    if(val)
    {
        return val.value().value;
    }
    return std::nullopt;
}

void KeyValueService::remove(const std::string& key)
{
    storage.remove(key);
}