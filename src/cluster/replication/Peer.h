#pragma once

#include <string>

struct Peer
{
    std::string host;
    int port;
    Peer(const std::string& host, int port) : host(host), port(port) {}
};