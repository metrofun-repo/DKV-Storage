#pragma once

#include "domain/cluster/model/NodeInfo.h"
#include <vector>

namespace app::entrypoint {

struct AppConfig
{
    domain::cluster::model::NodeInfo nodeInfo = { "nodeX", "127.0.0.1", 8080 };
    std::vector<domain::cluster::model::NodeInfo> nodes;
};

} // namespace app::entrypoint