#pragma once

namespace app::cluster::protocol {

struct HeartbeatPayload
{
    std::string nodeId = {};
    int64_t timestamp = 0;
};

} // namespace app::cluster::protocol