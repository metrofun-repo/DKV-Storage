#pragma once

#include <string_view>

#include "infrastructure/http/server/HttpResponse.h"
#include "application/cluster/protocol/InternalResponse.h"

namespace app::cluster::http {

class InternalHttpResponseWriter
{
    using HttpResponse = infra::http::server::HttpResponse;

public:
    static void from(HttpResponse& response, const protocol::InternalResponse& res);
    static void badRequest(HttpResponse& response, const std::string& msg);
};

} //namespace app::api::builders