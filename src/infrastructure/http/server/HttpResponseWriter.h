#pragma once

#include <iostream>
#include "HttpResponse.h"
#include "common/utils/json_utils.h"

namespace infra::http::server {

class HttpResponseWriter
{
public:
    static void write(HttpResponse& response, int statusCode, const common::json::json_t& data)
    {
        std::cout << data.dump(4) << std::endl;
        response.setStatus(statusCode);
        response.setContent(data.dump(), "application/json");
    }

    static void badRequest(HttpResponse& response, const std::string& msg)
    {
        write(response, /* bad request code */ 400, { {"error", msg} });
    }
};

} // namespace infra::http::server