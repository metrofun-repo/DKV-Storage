#include "HttplibResponseAdapter.h"
#include "third-party/httplib.h"

HttplibResponseAdapter::HttplibResponseAdapter(httplib::Response& res)
    : response(res)
{}

void HttplibResponseAdapter::setStatus(int code)
{
    response.status = code;
}
void HttplibResponseAdapter::setBody(const std::string& body)
{
    response.body = body;
}
void HttplibResponseAdapter::setHeader(const std::string& key, const std::string& value)
{
    response.set_header(key, value);
}

void HttplibResponseAdapter::setContent(const std::string& s, const std::string& contentType)
{
    response.set_content(s, contentType);
}