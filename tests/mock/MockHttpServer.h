#pragma once

#include <vector>
#include <string>

#include "interfaces/IHttpServer.h"

class MockHttpServer : public IHttpServer
{
public:
    struct Route
    {
        std::string method;
        std::string path;
        Route(const std::string& m, const std::string& p) : method(m), path(p) {}
    };

    std::vector<Route> routes;

    void set(const std::string& path, Handler) override
    {
        routes.emplace_back("POST", path);
    }

    void get(const std::string& path, Handler) override
    {
        routes.emplace_back("GET", path);
    }

    void remove(const std::string& path, Handler) override
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