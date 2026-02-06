#include "RoutesRegistrar.h"

#include "third-party/httplib.h"
#include "HttpMethodHandler.h"
#include "Routes.h"
#include "interfaces/IRequest.h"
#include "interfaces/IResponse.h"
#include "interfaces/IHttpServer.h"

RoutesRegistrar::RoutesRegistrar(HttpMethodHandler& hndlr) : handler(hndlr)
{}

void RoutesRegistrar::registerPublicRoutes(IHttpServer& server)
{
    server.set(Routes::Public::SET, [&](const IRequest& req, IResponse& res)
    {
        handler.handleSet(req, res);
    });

    server.get(Routes::Public::GET, [&](const IRequest& req, IResponse& res)
    {
        handler.handleGet(req, res);
    });

    server.remove(Routes::Public::REMOVE, [&](const IRequest& req, IResponse& res)
    {
        handler.handleRemove(req, res);
    });
}