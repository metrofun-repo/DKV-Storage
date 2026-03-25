#pragma once

#include "core/types/Error.h"
#include "ClusterErrorCode.h"

namespace app::cluster::protocol {

using ClusterError = core::types::Error<ClusterErrorCode>;

} // namespace app::cluster::protocol

