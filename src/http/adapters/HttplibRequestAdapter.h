#pragma once

#include "interfaces/IRequest.h"

namespace httplib { struct Request; }

class HttplibRequestAdapter : public IRequest
{
    const httplib::Request& request;
public:
    HttplibRequestAdapter(const httplib::Request& req);

    bool hasParam(const std::string& name) const override;
    std::string getParam(const std::string& name) const override;
    std::string getBody() const override;
};