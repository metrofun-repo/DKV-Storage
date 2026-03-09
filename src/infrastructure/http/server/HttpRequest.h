#pragma once

#include <string_view>

namespace infra::http::server {

class HttpRequest
{
public:
    virtual ~HttpRequest() = default;

    virtual bool hasParam(std::string_view param) const = 0;
    virtual std::string_view getParam(std::string_view param) const = 0;

    virtual bool hasHeader(std::string_view key) const = 0;
    virtual std::string_view getHeader(std::string_view key) const = 0;

    virtual std::string_view getBody() const = 0;
    virtual std::string_view getMethod() const = 0;
    virtual std::string_view getPath() const = 0;
};

} // namespace infra::http::server