#pragma once

#include <unordered_map>
#include "infrastructure/http/server/HttpRequest.h"

class MockRequest : public infra::http::server::HttpRequest
{
public:
    std::unordered_map<std::string, std::string> params;
    std::string body;
    std::string header;
    std::string method;
    std::string path;

    bool hasParam(std::string_view name) const override
    {
        return params.find(std::string(name)) != params.end();
    }
    std::string_view getParam(std::string_view name) const override
    {
        return params.at(std::string(name));
    }
    std::string_view getBody() const override
    {
        return body;
    }

    bool hasHeader(std::string_view key) const override
    {
        return false;
    }

    std::string_view getHeader(std::string_view key) const
    {
        return header;
    }

    std::string_view getMethod() const override
    {
        return method;
    }
    
    std::string_view getPath() const override
    {
        return path;
    }
};