#pragma once

#include "third-party/httplib.h"
#include "infrastructure/http/server/HttpResponse.h"

namespace infra::http::adapters::httplib::server {

class HttplibServerResponse : public http::server::HttpResponse
{
    using Response = ::httplib::Response;

public:
    explicit HttplibServerResponse(Response& raw);
    void setStatus(int code) override;
    void setBody(std::string body) override;
    void setHeader(std::string key, std::string value) override;
    void setContent(std::string body, std::string contentType) override;
    void setContent(const char* body, std::size_t n, std::string contentType) override;

private:
    Response& raw;
};

} // namespace infra::http::adapters::httplib::server