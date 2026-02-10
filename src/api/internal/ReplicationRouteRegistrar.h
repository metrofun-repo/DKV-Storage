#pragma once

class IHttpServer;
class ReplicationHttpHandler;

class ReplicationRouteRegistrar
{
    ReplicationHttpHandler& handler;
public:
    ReplicationRouteRegistrar(ReplicationHttpHandler& hndlr);
    void registerReplicationRoutes(IHttpServer& server);
};