#include "ClientResponseBuilder.h"

#include <iostream>
#include "infrastructure/http/server/HttpResponseWriter.h"

namespace {
    int mapHttpStatus(const app::api::dto::ClientResponse& resp)
    {
        if(resp.success) return 200;

        if(resp.status == "INVALID_REQUEST") return 400;

        return 500;
    }
}

namespace app::api::builders {

using infra::http::server::HttpResponseWriter;

void ClientResponseBuilder::from(HttpResponse& response, const app::api::dto::ClientResponse& clientRes)
{
    HttpResponseWriter::write(response, mapHttpStatus(clientRes), clientRes.toJson());
}

} // namespace app::api::builder