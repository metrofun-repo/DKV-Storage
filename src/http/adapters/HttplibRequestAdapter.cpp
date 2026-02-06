#include "HttplibRequestAdapter.h"
#include "third-party/httplib.h"

HttplibRequestAdapter::HttplibRequestAdapter(const httplib::Request& req)
    : request(req)
{}

bool HttplibRequestAdapter::hasParam(const std::string& name) const
{
    return request.has_param(name);
}

std::string HttplibRequestAdapter::getParam(const std::string& name) const
{
    return request.get_param_value(name);
}

std::string HttplibRequestAdapter::getBody() const
{
    return request.body;
}