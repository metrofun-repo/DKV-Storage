#include "KeyValueStorage.h"

namespace infra::storage::types {

using SetResult = core::types::Expected<void, error::RawStorageError>;
using GetResult = core::types::Expected<app::types::VersionedValue, error::RawStorageError>;

SetResult KeyValueStorage::rawSet(const app::types::Key& key, app::types::VersionedValue value)
{
    try
    {
        std::unique_lock lock { mtx };
        map.insert_or_assign(key, std::move(value));
    }
    catch(const std::bad_alloc&)
    {
        return SetResult::makeFailure(error::RawStorageError {
            error::RawStorageErrorCode::OutOfMemory,
            "Out of memory occured"
        });
    }
    catch(const std::exception&)
    {
        return SetResult::makeFailure(error::RawStorageError {
            error::RawStorageErrorCode::InternalError,
            "Internal storage error occured"
        });
    }
    return SetResult::makeSuccess();
}


GetResult KeyValueStorage::rawGet(const app::types::Key& key) const
{
    std::shared_lock lock { mtx };
    auto it = map.find(key);
    if(it == map.end())
    {
        return GetResult::makeSuccess(app::types::VersionedValue::tombstone(0));
    }
    
    return GetResult::makeSuccess(it->second);
}

void KeyValueStorage::compact()
{
    std::unique_lock lock { mtx };
    for(auto it = map.begin(); it != map.end();)
    {
        if(it->second.isTombstone())
        {
            it = map.erase(it);
        }
        else
        {
            ++it;
        }

    }
}


} // namespace infra::storage::types