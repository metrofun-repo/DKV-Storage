#include "ExternalHttpResponseWriter.h"

#include <iostream>
#include "infrastructure/serialization/JsonSerializer.h"
#include "infrastructure/http/server/HttpResponseWriter.h"
#include "infrastructure/serialization/traits/JsonTraitsExternalResponse.h"

namespace {
    int mapHttpStatus(const app::api::dto::ExternalResponse& resp)
    {
        if(resp.success) return 200;

        if(resp.status == "INVALID_REQUEST") return 400;

        return 500;
    }
}

namespace app::api::http {

using infra::serialization::JsonSerializer;

void ExternalHttpResponseWriter::from(HttpResponse& response, const api::dto::ExternalResponse& clientRes)
{
    infra::http::server::HttpResponseWriter::write(
        response,
        mapHttpStatus(clientRes),
        JsonSerializer::serialize(clientRes));
}

void ExternalHttpResponseWriter::badRequest(HttpResponse& response, const std::string& msg)
{
    from(response, { false, "INVALID_REQUEST", msg });
}

} // namespace app::api::builder