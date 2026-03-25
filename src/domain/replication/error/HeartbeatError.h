#pragma once

#include "core/types/Error.h"
#include "HeartbeatErrorCode.h"

namespace domain::replication::error {

using HeartbeatError = core::types::Error<HeartbeatErrorCode>;

} // namespace domain::replication::error