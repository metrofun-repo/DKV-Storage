#include "ReplicationHttpHandler.h"

#include "common/utils/json_utils.h"

#include "application/cluster/protocol/ReplicationRequest.h"
#include "application/cluster/builders/ReplicationResponseBuilder.h"
#include "infrastructure/http/server/HttpResponseWriter.h"
#include "infrastructure/http/validation/HttpRequestValidator.h"

namespace app::cluster::http {

using ReplicationResponseBuilder = cluster::builders::ReplicationResponseBuilder;
using ReplicationRequest         = cluster::protocol::ReplicationRequest;

using HttpRequestValidator       = infra::http::validation::HttpRequestValidator;
using HttpResponseWriter         = infra::http::server::HttpResponseWriter;

ReplicationHttpHandler::ReplicationHttpHandler(ReplicationWriteHandler& service)
    : writeHandler(service)
{
}

void ReplicationHttpHandler::handleReplicate(const HttpRequest& req, HttpResponse& res)
{
    auto valid = HttpRequestValidator::requireBody(req);
    if(!valid.hasValue())
    {
        HttpResponseWriter::badRequest(res, valid.error());
        return;
    }

    auto expJson = common::json::parse(req.getBody());
    if(!expJson.hasValue())
    {
        HttpResponseWriter::badRequest(res, expJson.error());
        return;
    }
    
    auto expReq = ReplicationRequest::fromJson(expJson.value());
    if(!expReq.hasValue())
    {
        HttpResponseWriter::badRequest(res, expReq.error());
        return;
    }

    auto applyResult = writeHandler.handle(expReq.value());
    if(!applyResult.hasValue())
    {
        HttpResponseWriter::badRequest(res, applyResult.error());
    }

    ReplicationResponseBuilder::from(res, applyResult.value());
}

} // namespace app::cluster::http