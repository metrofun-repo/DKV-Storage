#pragma once

#include <unordered_map>
#include "interfaces/IRequest.h"

class MockRequest : public IRequest
{
public:
    std::unordered_map<std::string, std::string> params;
    std::string body;

    bool hasParam(const std::string& name) const override
    {
        return params.find(name) != params.end();
    }
    std::string getParam(const std::string& name) const override
    {
        return params.at(name);
    }
    std::string getBody() const override
    {
        return body;
    }
};