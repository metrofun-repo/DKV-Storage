#include "HttpRequestRouter.h"

#include "Routes.h"

namespace infra::http::routing {

using HttpRequest = infra::http::server::HttpRequest;
using HttpResponse = infra::http::server::HttpResponse;

HttpRequestRouter::HttpRequestRouter(
        infra::http::server::HttpServer& server,
        app::api::http::ExternalHttpHandler& external,
        app::cluster::http::InternalHttpHandler& internal)
    : server(server)
    , extHndlr(external)
    , intHndlr(internal)
{
    initRoutes();
}

void HttpRequestRouter::initRoutes()
{
    server.set(infra::http::routing::routes::EXTERNAL, [&](const HttpRequest& req, HttpResponse& res)
    {
        extHndlr.handleRequest_POST(req, res);
    });

    server.get(infra::http::routing::routes::EXTERNAL, [&](const HttpRequest& req, HttpResponse& res)
    {
        extHndlr.handleRequest_GET(req, res);
    });

    server.remove(infra::http::routing::routes::EXTERNAL, [&](const HttpRequest& req, HttpResponse& res)
    {
        extHndlr.handleRequest_DELETE(req, res);
    });

    server.set(infra::http::routing::routes::INTERNAL, [&](const HttpRequest& req, HttpResponse& res)
    {
        intHndlr.handleRequest(req, res);
    });
}

}