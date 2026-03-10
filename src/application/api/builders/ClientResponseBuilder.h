#pragma once

#include <string_view>

#include "infrastructure/http/server/HttpResponse.h"
#include "application/api/responses/ClientResponse.h"

namespace app::api::builders {

class ClientResponseBuilder
{
    using HttpResponse = infra::http::server::HttpResponse;

public:
    static void from(HttpResponse& response, const app::api::dto::ClientResponse& clientRes);
};

} //namespace app::api::builders