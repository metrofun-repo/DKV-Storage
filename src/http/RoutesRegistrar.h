#pragma once

class IHttpServer;
class HttpMethodHandler;

class RoutesRegistrar
{
    HttpMethodHandler& handler;
public:
    RoutesRegistrar(HttpMethodHandler& hndlr);
    void registerPublicRoutes(IHttpServer& server);
};