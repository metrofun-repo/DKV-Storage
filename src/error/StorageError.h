#pragma once

namespace error {

enum class StorageError
{
    None = 0,
    KeyNotFound,
    StaleWrite,
    InternalError
};

} // namespace error