#pragma once

#include <string>
#include "StorageError.h"
#include "AppError.h"

namespace error {

enum class AppErrorType
{
    InvalidRequest,
    StorageFailure
};

struct AppError
{
    AppErrorType appError;
    StorageError storageError;
    std::string details;
};

} // namespace error