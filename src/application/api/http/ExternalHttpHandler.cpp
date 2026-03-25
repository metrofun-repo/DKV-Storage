#include "ExternalHttpHandler.h"

#include "application/api/http/ExternalHttpResponseWriter.h"

#include "infrastructure/http/validation/HttpRequestValidator.h"
#include "infrastructure/http/server/HttpResponseWriter.h"

namespace app::api::http {

using ExternalResponse = dto::ExternalResponse;
using ExternalRequest  = dto::ExternalRequest;

using HttpRequest        = infra::http::server::HttpRequest;
using HttpResponse       = infra::http::server::HttpResponse;
using HttpResponseWriter = infra::http::server::HttpResponseWriter;
using ExternalHttpResponseWriter = api::http::ExternalHttpResponseWriter;

ExternalHttpHandler::ExternalHttpHandler(storage::services::QueryService& q, cluster::services::ReplicationService& r)
    : query(q)
    , replication(r)
{}

void ExternalHttpHandler::handleRequest_POST(const HttpRequest& req, HttpResponse& res)
{
    auto keyValid = infra::http::validation::HttpRequestValidator::requireParam(req, "key");
    if(!keyValid.hasValue())
    {      
        return ExternalHttpResponseWriter::badRequest(res, keyValid.error());
    }

    auto body = infra::http::validation::HttpRequestValidator::requireBody(req);
    if(!body.hasValue())
    {      
        return ExternalHttpResponseWriter::badRequest(res, body.error());
    }

    auto json = common::json::parse(req.getBody());
    if(!json.hasValue())
    {
        return ExternalHttpResponseWriter::badRequest(res, json.error());
    }
    
    auto value = common::json::getValue<app::types::Value>(json.value(), "value");
    if(!value.hasValue())
    {
        return ExternalHttpResponseWriter::badRequest(res, value.error());
    }

    ExternalRequest request {
        ExternalRequest::OperationType::Set,
        std::string(req.getParam("key")),
        value.value()
    };

    ExternalHttpResponseWriter::from(res, replication.replicate(request));    
}

void ExternalHttpHandler::handleRequest_GET(const HttpRequest& req, HttpResponse& res)
{
    auto valid = infra::http::validation::HttpRequestValidator::requireParam(req, "key");
    if(!valid.hasValue())
    {
        return ExternalHttpResponseWriter::badRequest(res, valid.error());
    }

    ExternalRequest extReq {
        ExternalRequest::OperationType::Get,
        std::string(req.getParam("key"))
    };
    ExternalHttpResponseWriter::from(res, query.get(extReq));
}

void ExternalHttpHandler::handleRequest_DELETE(const HttpRequest& req, HttpResponse& res)
{
    auto valid = infra::http::validation::HttpRequestValidator::requireParam(req, "key");
    if(!valid.hasValue())
    {
        return ExternalHttpResponseWriter::badRequest(res, valid.error());
    }

    ExternalRequest extReq {
        ExternalRequest::OperationType::Delete,
        std::string(req.getParam("key")),
        std::nullopt
    };
    ExternalHttpResponseWriter::from(res, replication.replicate(extReq));  
}


} // namespace app::api::http