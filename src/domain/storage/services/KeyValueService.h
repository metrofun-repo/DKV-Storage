#pragma once

#include "error/StorageError.h"
#include "domain/storage/model/VersionedValue.h"
#include "infrastructure/storage/types/KeyValueStorage.h"

namespace domain::storage::services {
    
template <typename KeyT, typename ValueT>
class KeyValueService
{
    template <typename T>
    using Result = core::types::Expected<T, error::StorageError>;
    
    using StorageError    = error::StorageError;
    using RawStorageError = infra::storage::error::RawStorageError;
    using VersionedValue  = domain::storage::model::VersionedValue<ValueT>;

    using RawStorage = infra::storage::types::KeyValueStorage<KeyT, ValueT>;

public:
    explicit KeyValueService(RawStorage& storage) : storage(storage) {}

    Result<void> set(const KeyT& key, ValueT value, uint64_t timestamp)
    {
        auto rawGet = storage.rawGet(key);

        if(!rawGet.hasValue())
        {
            return Result<void>::makeFailure(StorageError::InternalError);
        }

        const auto& rawGetValue = rawGet.value();

        if(rawGetValue && rawGetValue->timestamp >= timestamp)
        {
            return Result<void>::makeFailure(StorageError::StaleWrite);
        }

        VersionedValue versionedValue { std::move(value), timestamp };

        auto rawSet = storage.rawSet(key, std::move(versionedValue));
        if(!rawSet.hasValue())
        {
            switch(rawSet.error())
            {
                case RawStorageError::InternalError : 
                case RawStorageError::OutOfMemory   :
                default                             : return Result<void>::makeFailure(StorageError::InternalError);
            }
        }
        return Result<void>::makeSuccess();
    }

    Result<VersionedValue> get(const KeyT& key)
    {
        auto rawGet = storage.rawGet(key);
        if(!rawGet.hasValue())
        {
            return Result<VersionedValue>::makeFailure(StorageError::InternalError);
        }

        const auto& rawGetValue = rawGet.value();

        if(!rawGetValue.has_value())
        {
            return Result<VersionedValue>::makeFailure(StorageError::KeyNotFound);
        }

        return Result<VersionedValue>::makeSuccess(rawGetValue.value());
    }

    Result<void> remove(const KeyT& key)
    {
        auto rawRemove = storage.rawRemove(key);
        if(!rawRemove.hasValue())
        {
            return Result<void>::makeFailure(StorageError::InternalError);
        }

        if(!rawRemove.value())
        {
            return Result<void>::makeFailure(StorageError::KeyNotFound);
        }

        return Result<void>::makeSuccess();
    }

private:
    RawStorage& storage;
};

} // namespace domain::storage::services