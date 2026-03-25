#pragma once

#include "domain/storage/services/KeyValueService.h"

namespace app::types {

using Storage        = infra::storage::types::KeyValueStorage;
using StorageService = domain::storage::services::KeyValueService;

}