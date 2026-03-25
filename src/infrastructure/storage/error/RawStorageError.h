#pragma once

#include "core/types/Error.h"
#include "RawStorageErrorCode.h"

namespace infra::storage::error {

using RawStorageError = core::types::Error<RawStorageErrorCode>;

}