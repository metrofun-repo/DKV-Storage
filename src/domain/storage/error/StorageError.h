#pragma once

#include "core/types/Error.h"
#include "StorageErrorCode.h"

namespace domain::storage::error {

using StorageError = core::types::Error<StorageErrorCode>;

} // namespace domain::storage::error