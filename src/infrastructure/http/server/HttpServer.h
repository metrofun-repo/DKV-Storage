#pragma once 

#include <string_view>
#include <functional>

namespace infra::http::server {

class HttpRequest;
class HttpResponse;

class HttpServer
{
public:
    using HandlerFunc = std::function<void(const HttpRequest& req, HttpResponse& res)>;

    virtual ~HttpServer() = default;

    virtual void set(std::string_view path, HandlerFunc handler) = 0;
    virtual void get(std::string_view path, HandlerFunc handler) = 0;
    virtual void remove(std::string_view path, HandlerFunc handler) = 0;

    virtual void start() = 0;
    virtual void stop() = 0;
};

} // namespace infra::http::server