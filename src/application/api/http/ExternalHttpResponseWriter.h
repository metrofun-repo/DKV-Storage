#pragma once

#include <string_view>

#include "infrastructure/http/server/HttpResponse.h"
#include "application/api/responses/ExternalResponse.h"

namespace app::api::http {

class ExternalHttpResponseWriter
{
    using HttpResponse = infra::http::server::HttpResponse;

public:
    static void from(HttpResponse& response, const api::dto::ExternalResponse& clientRes);
    static void badRequest(HttpResponse& response, const std::string& msg);
};

} //namespace app::api::builders