#pragma once

#include "third-party/httplib.h"
#include "interfaces/IHttpServer.h"

class HttpServer : public IHttpServer
{    
    std::string host;
    int port;
    httplib::Server srv;
public:
    HttpServer(const std::string& host, int port);

    void set(const std::string& path, Handler handler) override;
    void get(const std::string& path, Handler handler) override;
    void remove(const std::string& path, Handler handler) override;

    void start() override;
    void stop() override;
};