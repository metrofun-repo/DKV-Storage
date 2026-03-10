#pragma once

#include "Routes.h"
#include "infrastructure/http/server/HttpServer.h"
#include "infrastructure/http/server/HttpRequest.h"
#include "infrastructure/http/server/HttpResponse.h"

#include "application/api/http/PublicHttpHandler.h"
#include "application/cluster/http/ReplicationHttpHandler.h"

namespace infra::http::routing {

class HttpRequestRouter
{
    using HttpServer = infra::http::server::HttpServer;
    using HttpRequest = infra::http::server::HttpRequest;
    using HttpResponse = infra::http::server::HttpResponse;

    using PublicHandler  = app::api::http::PublicHttpHandler;
    using ReplicaHandler = app::cluster::http::ReplicationHttpHandler;

public:
    explicit HttpRequestRouter(HttpServer& server, PublicHandler& pub, ReplicaHandler& rep) 
        : server(server)
        , pubHndlr(pub)
        , repHndlr(rep)
    {
        initRoutes();
    }

private:
    void initRoutes()
    {
        server.set(infra::http::routing::routes::PUBLIC, [&](const HttpRequest& req, HttpResponse& res)
        {
            pubHndlr.handleRequest(req, res);
        });

        server.set(infra::http::routing::routes::REPLICATE, [&](const HttpRequest& req, HttpResponse& res)
        {
            repHndlr.handleReplicate(req, res);
        });
    }

    HttpServer& server;
    PublicHandler& pubHndlr;
    ReplicaHandler& repHndlr;
};

} // namespace infra::http::server