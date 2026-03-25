#include "InternalHttpResponseWriter.h"

#include "infrastructure/serialization/JsonSerializer.h"
#include "infrastructure/http/server/HttpResponseWriter.h"
#include "application/cluster/protocol/InternalResponse.h"
#include "infrastructure/serialization/traits/JsonTraitsInternalResponse.h"

namespace app::cluster::http {

using InternalResponse   = protocol::InternalResponse;

using HttpResponseWriter = infra::http::server::HttpResponseWriter;
using JsonSerializer     = infra::serialization::JsonSerializer;


void InternalHttpResponseWriter::from(HttpResponse& response, const InternalResponse& res)
{
    HttpResponseWriter::write(response, 200, JsonSerializer::serialize(res));
}
void InternalHttpResponseWriter::badRequest(HttpResponse& response, const std::string& msg)
{
    InternalResponse res;
    res.type = InternalResponse::Type::Invalid;
    res.error = protocol::ClusterError {
        protocol::ClusterErrorCode::InvalidRequest,
        msg
    };
    from(response, res);
}
} // namespace app::cluster::builders