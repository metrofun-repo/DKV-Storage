#pragma once

class IHttpServer;
class PublicHttpHandler;

class PublicRouteRegistrar
{
    PublicHttpHandler& handler;
public:
    PublicRouteRegistrar(PublicHttpHandler& hndlr);
    void registerPublicRoutes(IHttpServer& server);
};