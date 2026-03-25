#pragma once

namespace infra::storage::error {

enum class RawStorageErrorCode
{
    OutOfMemory,
    InternalError
};

} // namespace infra::storage::error