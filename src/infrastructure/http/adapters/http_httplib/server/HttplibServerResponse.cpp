#include "HttplibServerResponse.h"

namespace infra::http::adapters::httplib::server {

HttplibServerResponse::HttplibServerResponse(Response& raw)
    : raw(raw)
{}

void HttplibServerResponse::setStatus(int code)
{
    raw.status = code;
}

void HttplibServerResponse::setBody(std::string body)
{
    raw.body = std::move(body);
}

void HttplibServerResponse::setHeader(std::string key, std::string value)
{
    raw.set_header(std::move(key), std::move(value));
}

void HttplibServerResponse::setContent(std::string body, std::string contentType)
{
    raw.set_content(std::move(body), std::move(contentType));
}

void HttplibServerResponse::setContent(const char* body, std::size_t n, std::string contentType)
{
    raw.set_content(body, n, std::move(contentType));
}


} // namespace infra::http::adapters::httplib::server