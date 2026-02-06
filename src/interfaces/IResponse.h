#pragma once

#include <string>

class IResponse
{
public:
    virtual void setStatus(int code) = 0;
    virtual void setBody(const std::string& body) = 0;
    virtual void setHeader(const std::string& key, const std::string& value) = 0;
    virtual void setContent(const std::string& s, const std::string& contentType) = 0;
    
    virtual ~IResponse() = default;
};