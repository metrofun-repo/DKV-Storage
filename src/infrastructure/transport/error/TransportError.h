#pragma once

#include "core/types/Error.h"
#include "TransportErrorCode.h"

namespace infra::transport::error {

using TransportError = core::types::Error<TransportErrorCode>;

} // namespace infra::transport::senders