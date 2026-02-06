#include "HttpServer.h"

HttpServer::HttpServer(const std::string& host, int port)
    : host(host)
    , port(port)
{}

void HttpServer::start()
{
    std::cout << "[" << host << ":" << port <<"] listening '0.0.0.0: " << port << "'" << std::endl;
    bool result = srv.listen("0.0.0.0", port);
    if(!result)
    {
        std::cout << "[" << host << ":" << port <<"] listen attempt failed" << std::endl;
    }
}

void HttpServer::stop()
{
    srv.stop();
}