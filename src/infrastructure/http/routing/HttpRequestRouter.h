#pragma once

#include "infrastructure/http/server/HttpServer.h"
#include "infrastructure/http/server/HttpRequest.h"
#include "infrastructure/http/server/HttpResponse.h"

#include "application/api/http/ExternalHttpHandler.h"
#include "application/cluster/http/InternalHttpHandler.h"

namespace infra::http::routing {

class HttpRequestRouter
{
public:
    explicit HttpRequestRouter(
        server::HttpServer& server,
        app::api::http::ExternalHttpHandler& external,
        app::cluster::http::InternalHttpHandler& internal);
private:
    void initRoutes();

    http::server::HttpServer& server;
    app::api::http::ExternalHttpHandler& extHndlr;
    app::cluster::http::InternalHttpHandler& intHndlr;
};

} // namespace infra::http::server