#pragma once

#include "BasicError.h"
#include "core/types/Expected.h"

namespace core::types {

template <typename T>
using BasicResult = Expected<T, BasicError>;

} // namespace core::types