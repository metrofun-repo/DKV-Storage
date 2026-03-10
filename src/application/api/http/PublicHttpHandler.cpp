#include "PublicHttpHandler.h"

#include "common/utils/json_utils.h"
#include "infrastructure/http/validation/HttpRequestValidator.h"
#include "infrastructure/http/server/HttpResponseWriter.h"

#include "application/api/builders/ClientResponseBuilder.h"

namespace app::api::http {

using ClientResponseBuilder = app::api::builders::ClientResponseBuilder;

using HttpResponseWriter    = infra::http::server::HttpResponseWriter;

PublicHttpHandler::PublicHttpHandler(ClientReadHandler& r, ClientWriteHandler& w)
    : readHandler(r)
    , writeHandler(w)
{}

void PublicHttpHandler::handleRequest(const infra::http::server::HttpRequest& req,infra::http::server::HttpResponse& res)
{
    auto valid = infra::http::validation::HttpRequestValidator::requireBody(req);
    if(!valid.hasValue())
    {
        HttpResponseWriter::badRequest(res, valid.error());
        return;
    }

    auto json = common::json::parse(req.getBody());
    if(!json.hasValue())
    {
        HttpResponseWriter::badRequest(res, json.error());
        return;
    }
    
    auto clientReq = app::api::dto::ClientRequest::fromJson(json.value());
    if(!clientReq.hasValue())
    {
        HttpResponseWriter::badRequest(res, clientReq.error());
        return;
    }

    auto request = clientReq.value();
    ClientResponse response;

    if(request.isReadRequest())
    {
        auto read = readHandler.handle(request);
        if(!read.hasValue())
        {
            HttpResponseWriter::badRequest(res, read.error());
        }
        response = read.value();
    }
    else
    {
        auto write = writeHandler.handle(request);
        if(!write.hasValue())
        {
            HttpResponseWriter::badRequest(res, write.error());
        }
        response = write.value();
    }

    ClientResponseBuilder::from(res, response);    
}

} // namespace app::api::http