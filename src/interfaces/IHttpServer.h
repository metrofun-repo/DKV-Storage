#pragma once

#include <string>
#include <functional>

class IRequest;
class IResponse;

class IHttpServer
{
public:
    using Handler = std::function<void(const IRequest& req, IResponse& res)>;
    
    virtual void set(const std::string& path, Handler handler) = 0;
    virtual void get(const std::string& path, Handler handler) = 0;
    virtual void remove(const std::string& path, Handler handler) = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual ~IHttpServer() = default;
};