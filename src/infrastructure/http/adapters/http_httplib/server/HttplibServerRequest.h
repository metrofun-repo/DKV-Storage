#pragma once

#include "third-party/httplib.h"
#include "infrastructure/http/server/HttpRequest.h"

namespace infra::http::adapters::httplib::server {

class HttplibServerRequest : public infra::http::server::HttpRequest
{
    using Request = ::httplib::Request;

public:
    explicit HttplibServerRequest(const Request& raw);

    bool hasParam(std::string_view param) const override;
    std::string getParam(std::string_view param) const override;

    bool hasHeader(std::string_view key) const override;
    std::string_view getHeader(std::string_view key) const override;

    std::string_view getBody() const override;
    std::string_view getMethod() const override;
    std::string_view getPath() const override;
private:
    const Request& raw;
};

} // namespace infra::http::adapters::httplib::server