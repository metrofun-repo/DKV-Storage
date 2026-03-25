#include "InternalHttpHandler.h"

#include "common/utils/json_utils.h"

#include "application/cluster/http/InternalHttpResponseWriter.h"
#include "application/cluster/protocol/InternalRequest.h"

#include "infrastructure/http/server/HttpResponseWriter.h"
#include "infrastructure/http/validation/HttpRequestValidator.h"

#include "infrastructure/serialization/JsonSerializer.h"
#include "infrastructure/serialization/traits/JsonTraitsInternalRequest.h"

namespace app::cluster::http {

using ReplicationPayload = protocol::ReplicationPayload;
using HeartbeatPayload   = protocol::HeartbeatPayload;

using InternalRequest    = protocol::InternalRequest;
using InternalResponse   = protocol::InternalResponse;

using HttpRequestValidator = infra::http::validation::HttpRequestValidator;
using HttpResponseWriter   = infra::http::server::HttpResponseWriter;
using Serializer           = infra::serialization::JsonSerializer;

InternalHttpHandler::InternalHttpHandler(
        cluster::services::HeartbeatService& hb,
        cluster::services::ReplicationService& rp)
    : hbService(hb)
    , rpService(rp)
{}

void InternalHttpHandler::handleRequest(const infra::http::server::HttpRequest& req, infra::http::server::HttpResponse& res)
{
    auto valid = HttpRequestValidator::requireBody(req);
    if(!valid.hasValue())
    {
        return InternalHttpResponseWriter::badRequest(res, valid.error());
    }
    
    auto intRequest = Serializer::deserialize<InternalRequest>(req.getBody());
    if(!intRequest.hasValue())
    {
        return InternalHttpResponseWriter::badRequest(res, intRequest.error());
    }

    const auto& request = intRequest.value();
    switch(request.type)
    {
        case InternalRequest::Type::Heartbeat: 
            return InternalHttpResponseWriter::from(res, hbService.apply(request));
        case InternalRequest::Type::Replication:
            return InternalHttpResponseWriter::from(res, rpService.apply(request));
        default:
            return InternalHttpResponseWriter::badRequest(res, "Invalid cluster request");
    }
}

} // namespace app::cluster::http