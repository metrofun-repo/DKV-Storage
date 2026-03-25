#pragma once
#include "core/types/Error.h"
#include "AppErrorCode.h"

namespace error {

using AppError = core::types::Error<AppErrorCode>;

} // namespace error