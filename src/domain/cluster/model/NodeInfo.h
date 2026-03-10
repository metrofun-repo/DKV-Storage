#pragma once

#include <string>

namespace domain::cluster::model {

struct NodeInfo
{
    std::string nodeId;
    std::string host;
    int port;   
    NodeInfo(std::string id = "", std::string host = "", int port = 0)
        : nodeId(std::move(id))
        , host(std::move(host))
        , port(port)
    {}
};

} // namespace domain::cluster::model