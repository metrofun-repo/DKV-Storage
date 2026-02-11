#pragma once

#include "cluster/replication/Peer.h"
#include <vector>

struct AppConfig
{
    int port;
    std::string host;
    std::vector<Peer> peers;

    AppConfig() = default;

    AppConfig(const AppConfig& other) = delete;
    AppConfig& operator=(AppConfig& other) = delete;
    
    AppConfig(AppConfig&& other) noexcept = default;
    AppConfig& operator=(AppConfig&& other) noexcept = default;
};