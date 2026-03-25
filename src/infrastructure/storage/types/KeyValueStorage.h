#pragma once

#include <shared_mutex>
#include <unordered_map>
#include "core/types/Expected.h"
#include "application/types/KeyValueTypes.h"
#include "infrastructure/storage/error/RawStorageError.h"

namespace infra::storage::types {

class KeyValueStorage
{
public:
    core::types::Expected<void, error::RawStorageError>
    rawSet(const app::types::Key& key, app::types::VersionedValue value);

    core::types::Expected<app::types::VersionedValue, error::RawStorageError>
    rawGet(const app::types::Key& key) const;

    // cleanup/compaction  
    void compact();
    
private:
    mutable std::shared_mutex mtx;
    std::unordered_map<app::types::Key, app::types::VersionedValue> map;
};

} // namespace infra::storage::types