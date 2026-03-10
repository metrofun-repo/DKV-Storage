#pragma once

#include "KeyValueTypes.h"
#include "domain/storage/services/KeyValueService.h"
#include "infrastructure/storage/types/KeyValueStorage.h"

namespace app::types {

using Storage        = infra::storage::types::KeyValueStorage<Key, Value>;
using StorageService = domain::storage::services::KeyValueService<Key, Value>;

}