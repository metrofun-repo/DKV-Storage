#pragma once

#include <unordered_map>
#include "infrastructure/http/server/HttpResponse.h"

class MockResponse : public infra::http::server::HttpResponse
{
public:
    int status;
    std::string body;
    std::unordered_map<std::string, std::string> headers;

    void setStatus(int code) override
    {
        status = code;
    }

    void setBody(std::string bdy) override
    {
        body = std::move(bdy);
    }

    void setHeader(std::string key, std::string value) override
    {
        headers[std::move(key)] = std::move(value);
    }

    void setContent(std::string body, std::string contentType) override
    {
        body = std::move(body);
    }
};