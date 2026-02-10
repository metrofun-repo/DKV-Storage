#include "PublicRouteRegistrar.h"

#include "third-party/httplib.h"

#include "PublicHttpHandler.h"

#include "api/public/Routes.h"

#include "interfaces/IRequest.h"
#include "interfaces/IResponse.h"
#include "interfaces/IHttpServer.h"

PublicRouteRegistrar::PublicRouteRegistrar(PublicHttpHandler& hndlr) : handler(hndlr)
{}

void PublicRouteRegistrar::registerPublicRoutes(IHttpServer& server)
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