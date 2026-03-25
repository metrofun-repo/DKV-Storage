#pragma once

namespace domain::storage::error {

enum class StorageErrorCode
{
    None = 0,
    StaleWrite,
    InternalError
};

} // namespace domain::storage::error