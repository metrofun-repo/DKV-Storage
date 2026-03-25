#pragma once

#include <string>

namespace infra::http::server {

class HttpResponse
{
public:
    virtual ~HttpResponse() = default;

    virtual void setStatus(int code) = 0;
    virtual void setBody(std::string body) = 0;
    virtual void setHeader(std::string key, std::string value) = 0;
    virtual void setContent(std::string body, std::string contentType) = 0;
    virtual void setContent(const char* body, std::size_t n, std::string contentType) = 0;
};

} // namespace infra::http::server