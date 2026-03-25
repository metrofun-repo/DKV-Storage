#pragma once

#include "domain/replication/FanoutResult.h"
#include "domain/replication/error/HeartbeatError.h"

namespace domain::replication {

using HeartbeatFanoutResult = domain::replication::FanoutResult<error::HeartbeatError>;

} // namespace domain::replication