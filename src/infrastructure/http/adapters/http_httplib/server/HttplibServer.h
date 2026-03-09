#pragma once

#include "third-party/httplib.h"
#include "domain/cluster/model/NodeInfo.h"
#include "infrastructure/http/server/HttpServer.h"

namespace infra::http::adapters::httplib::server {

class HttplibServer : public infra::http::server::HttpServer
{
    using libServer = ::httplib::Server;
    using NodeInfo = domain::cluster::model::NodeInfo;

public:
    explicit HttplibServer(NodeInfo info);
    explicit HttplibServer(std::string nodeId, std::string host, int port);

    void set(const std::string& path, HandlerFunc handler) override;
    void get(const std::string& path, HandlerFunc handler) override;
    void remove(const std::string& path, HandlerFunc handler) override;

    void start() override;
    void stop() override;

private:
    void printServerInfo(std::string_view msg) const;

    NodeInfo nodeInfo;
    libServer srv;
};

} // namespace infra::http::adapters::httplib::server