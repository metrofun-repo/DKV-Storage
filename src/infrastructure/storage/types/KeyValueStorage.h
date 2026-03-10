#pragma once

#include <unordered_map>
#include "domain/storage/model/VersionedValue.h"
#include "infrastructure/storage/error/RawStorageError.h"

namespace infra::storage::types {

template< typename KeyT, typename ValueT>
class KeyValueStorage
{
    using RawStorageError = infra::storage::error::RawStorageError;

    template <typename T>
    using RawResult = core::types::Expected<T, RawStorageError>;
    
    using VersionedValue = domain::storage::model::VersionedValue<ValueT>;

public:
    RawResult<void> rawSet(const KeyT& key, VersionedValue value)
    {
        try
        {
            map.emplace(key, std::move(value));
        }
        catch(const std::bad_alloc&)
        {
            return RawResult<void>::makeFailure(RawStorageError::OutOfMemory);
        }
        catch(const std::exception&)
        {
            return RawResult<void>::makeFailure(RawStorageError::InternalError);
        }

        return RawResult<void>::makeSuccess();
    }
    RawResult<std::optional<VersionedValue>> rawGet(const KeyT& key) const
    {
        auto it = map.find(key);
        if(it == map.end())
        {
            return RawResult<std::optional<VersionedValue>>::makeSuccess(std::nullopt);
        }
        return RawResult<std::optional<VersionedValue>>::makeSuccess(it->second);
    }

    RawResult<bool> rawRemove(const KeyT& key)
    {
        auto it = map.find(key);
        if(it == map.end())
        {
            return RawResult<bool>::makeSuccess(false);
        }

        map.erase(it);
        return RawResult<bool>::makeSuccess(true);
    }
private:
    std::unordered_map<KeyT, VersionedValue> map;
};

} // namespace infra::storage::types