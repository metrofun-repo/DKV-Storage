#pragma once

#include <string>

class IRequest
{
public:
    virtual bool hasParam(const std::string& name) const = 0;
    virtual std::string getParam(const std::string& name) const = 0;
    virtual std::string getBody() const = 0;

    virtual ~IRequest() = default;
};