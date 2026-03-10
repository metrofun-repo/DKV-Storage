#pragma once 

#include <string>
#include <functional>

namespace infra::http::server {

class HttpRequest;
class HttpResponse;

class HttpServer
{
public:
    using HandlerFunc = std::function<void(const HttpRequest& req,infra::http::server::HttpResponse& res)>;

    virtual ~HttpServer() = default;

    virtual void set(const std::string& path, HandlerFunc handler) = 0;
    virtual void get(const std::string& path, HandlerFunc handler) = 0;
    virtual void remove(const std::string& path, HandlerFunc handler) = 0;

    virtual void start() = 0;
    virtual void stop() = 0;
};

} // namespace infra::http::server