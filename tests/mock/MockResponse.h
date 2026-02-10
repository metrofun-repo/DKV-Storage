#pragma once

#include <unordered_map>
#include "interfaces/IResponse.h"


class MockResponse : public IResponse
{
public:
    int status;
    std::string body;
    std::unordered_map<std::string, std::string> headers;

    void setStatus(int code) override
    {
        status = code;
    }

    void setBody(const std::string& bdy) override
    {
        body = bdy;
    }

    void setHeader(const std::string& key, const std::string& value) override
    {
        headers[key] = value;
    }

    void setContent(const std::string& s, const std::string& contentType) override
    {
        body = s;
    }
};