#include "KeyValueService.h"

namespace domain::storage::services {

using SetResult = core::types::Expected<void, error::StorageError>;
using GetResult = core::types::Expected<app::types::VersionedValue, error::StorageError>;

KeyValueService::KeyValueService(infra::storage::types::KeyValueStorage& storage)
    : storage(storage)
{}

SetResult KeyValueService::set(const app::types::Key& key, app::types::VersionedValue value)
{
    auto local = storage.rawGet(key);
    if(!local.hasValue())
    {
        return SetResult::makeFailure(error::StorageError {
            error::StorageErrorCode::InternalError,
            local.error().message
        });           
    }

    const app::types::VersionedValue& localValue = local.value();
    if(localValue.timestamp > value.timestamp)
    {
        return SetResult::makeFailure(error::StorageError {
            error::StorageErrorCode::StaleWrite,
            "Incoming timestamp is older"
        });
    }

    auto rawSet = storage.rawSet(key, value);
    if(!rawSet.hasValue())
    {
        return SetResult::makeFailure(error::StorageError {
            error::StorageErrorCode::InternalError,
            rawSet.error().message
        });
    }
    return SetResult::makeSuccess();
}

GetResult KeyValueService::get(const app::types::Key& key)
{
    auto rawGetValue = storage.rawGet(key);
    if(!rawGetValue.hasValue())
    {
        return GetResult::makeFailure(error::StorageError {
            error::StorageErrorCode::InternalError,
            rawGetValue.error().message
        });
    }

    return GetResult::makeSuccess(rawGetValue.value());
}

} // namespace domain::storage::services