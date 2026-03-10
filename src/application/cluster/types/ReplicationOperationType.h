#pragma once

namespace app::cluster::types {

enum class ReplicationOperationType
{
    Unknown = 0,
    Set,
    Delete
};

} // namespace app::cluster::types