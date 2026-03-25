#pragma once

#include "application/types/KeyValueTypes.h"

namespace app::cluster::protocol {

struct ReplicationPayload
{
    std::string key = {};
    app::types::VersionedValue value;
};

} // namespace app::cluster::protocol