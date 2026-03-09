#pragma once

namespace app::api::types {

enum class ClientOperationType
{
    Unknown = 0,
    Get,
    Set,
    Delete
};

} // namespace app::api::types