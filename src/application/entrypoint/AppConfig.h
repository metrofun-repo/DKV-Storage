#pragma once

#include "domain/cluster/model/NodeInfo.h"
#include <vector>
#include <chrono>

namespace app::entrypoint {

struct AppConfig
{
    domain::cluster::model::NodeInfo nodeInfo = { "nodeX", "127.0.0.1", 8080 };
    std::vector<domain::cluster::model::NodeInfo> nodes;

    std::size_t quorumThreshold = 1;
    std::chrono::milliseconds hbPeriod = std::chrono::milliseconds(1000);
    std::chrono::milliseconds suspectThreshold = std::chrono::milliseconds(3000);
    std::chrono::milliseconds deadThreshold = std::chrono::milliseconds(5000);
    
    std::chrono::milliseconds compactionPeriod = std::chrono::milliseconds(3000);
};

} // namespace app::entrypoint