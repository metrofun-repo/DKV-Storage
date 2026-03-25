#pragma once

#include "application/types/KeyValueTypes.h"
#include "domain/storage/error/StorageError.h"
#include "infrastructure/storage/types/KeyValueStorage.h"

namespace domain::storage::services {
    
class KeyValueService
{
public:
    explicit KeyValueService(infra::storage::types::KeyValueStorage& storage);

    core::types::Expected<void, error::StorageError>
    set(const app::types::Key& key, app::types::VersionedValue value);

    core::types::Expected<app::types::VersionedValue, error::StorageError>
    get(const app::types::Key& key);

private:
    infra::storage::types::KeyValueStorage& storage;
};

} // namespace domain::storage::services