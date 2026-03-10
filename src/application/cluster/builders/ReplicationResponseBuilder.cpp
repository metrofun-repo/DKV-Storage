#include "ReplicationResponseBuilder.h"

#include "infrastructure/http/server/HttpResponseWriter.h"

namespace app::cluster::builders {

using infra::http::server::HttpResponseWriter;

void ReplicationResponseBuilder::from(HttpResponse& response, const app::cluster::types::ReplicationApplyResult& res)
{
    HttpResponseWriter::write(response, (res.applied ? 200 : 500), res.toJson());
}


} // namespace app::cluster::builders