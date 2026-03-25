#pragma once

#include <vector>
#include <string>

#include "infrastructure/http/server/HttpServer.h"

class MockHttpServer : public infra::http::server::HttpServer
{
public:
    struct Route
    {
        std::string method;
        std::string path;
        Route(std::string_view m, std::string_view p) : method(std::string(m)), path(std::string(p)) {}
    };

    std::vector<Route> routes;

    void set(std::string_view path, HandlerFunc) override
    {
        routes.emplace_back("POST", path);
    }

    void get(std::string_view path, HandlerFunc) override
    {
        routes.emplace_back("GET", path);
    }

    void remove(std::string_view path, HandlerFunc) override
    {
        routes.emplace_back("DELETE", path);
    }

    void start() override
    {

    }

    void stop() override
    {

    }
    
};