#pragma once

#include "domain/replication/FanoutResult.h"
#include "domain/replication/error/ReplicationError.h"

namespace domain::replication {

using ReplicationFanoutResult = domain::replication::FanoutResult<error::ReplicationError>;

} // namespace domain::replication