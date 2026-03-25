#pragma once

#include <optional>
#include "domain/replication/error/ReplicationError.h"

namespace domain::replication {

struct ReplicationResponsePayload
{
    bool applied = false;
    error::ReplicationError error;
};

// using ReplicationResponsePayload = core::types::Expected<void, error::ReplicationError>;

} // namespace app::cluster::protocol