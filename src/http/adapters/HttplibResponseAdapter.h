#pragma once

#include "interfaces/IResponse.h"

namespace httplib { class Response; }

class HttplibResponseAdapter : public IResponse
{
    httplib::Response& response;
public:
    HttplibResponseAdapter(httplib::Response& res);
    void setStatus(int code) override;
    void setBody(const std::string& body) override;
    void setHeader(const std::string& key, const std::string& value) override;
    void setContent(const std::string& s, const std::string& contentType) override;
};