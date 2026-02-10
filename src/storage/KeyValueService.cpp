#include "KeyValueService.h"

#include "storage/KeyValueStorage.h"

KeyValueService::KeyValueService(KeyValueStorage& storage)
    : storage(storage)
{
}

void KeyValueService::set(const std::string& key, const std::string& value, uint64_t timestamp)
{
    storage.put(key, value, timestamp);
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