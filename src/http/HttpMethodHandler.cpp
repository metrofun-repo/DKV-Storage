#include "HttpMethodHandler.h"

#include <chrono>

#include "interfaces/IRequest.h"
#include "interfaces/IResponse.h"

#include "http/Routes.h"
#include "http/HttpServer.h"
#include "http/HttpConstants.h"

#include "service/KeyValueService.h"

HttpMethodHandler::HttpMethodHandler(KeyValueService& service) : service(service) {}

void HttpMethodHandler::handleSet(const IRequest& req, IResponse& res)
{
    if(!req.hasParam(Http::Param::KEY))
    {
        res.setStatus(httplib::StatusCode::BadRequest_400);
        res.setContent("Missing param 'key'", "text/plain");
        return;
    }

    if(req.getBody().empty())
    {
        res.setStatus(httplib::StatusCode::BadRequest_400);
        res.setContent("Request 'body' is empty", "text/plain");
        return;
    }

    auto key = req.getParam(Http::Param::KEY);

    service.set(key, req.getBody());

    res.setStatus(httplib::StatusCode::OK_200);
    res.setContent("Value succesfully saved", "text/plain");
}

void HttpMethodHandler::handleGet(const IRequest& req, IResponse& res)
{
    if(!req.hasParam(Http::Param::KEY))
    {
        res.setStatus(httplib::StatusCode::BadRequest_400);
        res.setContent("Missing param 'key'", "text/plain");
        return;
    }

    auto key = req.getParam(Http::Param::KEY);
    auto value = service.get(key);

    if(!value.has_value())
    {
        res.setStatus(httplib::StatusCode::NotFound_404);
        res.setContent("No value found in storage", "text/plain");
        return;
    }
    res.setStatus(httplib::OK_200);
    res.setContent(value.value(), "text/plain");
}
void HttpMethodHandler::handleRemove(const IRequest& req, IResponse& res)
{
    if(!req.hasParam(Http::Param::KEY))
    {
        res.setStatus(httplib::StatusCode::BadRequest_400);
        res.setContent("Missing param 'key'", "text/plain");
        return;
    }
    auto key = req.getParam(Http::Param::KEY);
    service.remove(key);

    res.setStatus(httplib::StatusCode::OK_200);
    res.setContent("Value succesfully removed", "text/plain");
}