#pragma once

#include "core/types/Error.h"
#include "ReplicationErrorCode.h"

namespace domain::replication::error {

using ReplicationError = core::types::Error<ReplicationErrorCode>;

} // namespace domain::replication::error