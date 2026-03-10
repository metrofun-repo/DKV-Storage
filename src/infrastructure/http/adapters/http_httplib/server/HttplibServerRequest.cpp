#include "HttplibServerRequest.h"

namespace infra::http::adapters::httplib::server {

HttplibServerRequest::HttplibServerRequest(const Request& raw)
    : raw(raw)
{}
    
bool HttplibServerRequest::hasParam(std::string_view param) const
{
    return raw.has_param(param.data());
}

std::string_view HttplibServerRequest::getParam(std::string_view param) const
{
    return raw.get_param_value(param.data());
}

bool HttplibServerRequest::hasHeader(std::string_view key) const
{
    return raw.has_header(key.data());
}

std::string_view HttplibServerRequest::getHeader(std::string_view key) const
{
    return raw.get_header_value(key.data());
}

std::string_view HttplibServerRequest::getBody() const
{
    return raw.body;
}

std::string_view HttplibServerRequest::getMethod() const
{
    return raw.method;
}

std::string_view HttplibServerRequest::getPath() const
{
    return raw.path;
}

} // namespace infra::http::adapters::httplib::server