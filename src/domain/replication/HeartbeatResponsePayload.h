#pragma once

#include "domain/replication/error/HeartbeatError.h"

namespace domain::replication {

struct HeartbeatResponsePayload
{
    bool applied = false;
    error::HeartbeatError error;
};

// using HeartbeatResponsePayload = core::types::Expected<void, error::HeartbeatError>;

} // namespace domain::replication