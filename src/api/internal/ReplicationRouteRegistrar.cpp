#include "ReplicationRouteRegistrar.h"

#include "third-party/httplib.h"

#include "api/internal/ReplicationHttpHandler.h"

#include "api/internal/Routes.h"

#include "interfaces/IRequest.h"
#include "interfaces/IResponse.h"
#include "interfaces/IHttpServer.h"

ReplicationRouteRegistrar::ReplicationRouteRegistrar(ReplicationHttpHandler& hndlr)
    : handler(hndlr)
{}

void ReplicationRouteRegistrar::registerReplicationRoutes(IHttpServer& server)
{
    server.set(ReplicationRoutes::REPLICATE, [&](const IRequest& req, IResponse& res)
    {
        handler.handleReplicate(req, res);
    });
}