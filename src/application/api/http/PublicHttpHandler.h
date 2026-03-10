#pragma once

#include <unordered_map>
#include <functional>

#include "application/api/handlers/ClientReadHandler.h"
#include "application/api/handlers/ClientWriteHandler.h"

#include "infrastructure/http/server/HttpRequest.h"
#include "infrastructure/http/server/HttpResponse.h"

namespace app::api::http {

class PublicHttpHandler
{
    using HttpRequest  = infra::http::server::HttpRequest;
    using HttpResponse = infra::http::server::HttpResponse;

    using ClientResponse = app::api::dto::ClientResponse;
    using ClientRequest  = app::api::dto::ClientRequest;

    using ClientReadHandler = app::api::handlers::ClientReadHandler;
    using ClientWriteHandler = app::api::handlers::ClientWriteHandler;

public:
    explicit PublicHttpHandler(ClientReadHandler& r, ClientWriteHandler& w);

    void handleRequest(const HttpRequest& req, HttpResponse& res);

private:

    ClientReadHandler& readHandler;
    ClientWriteHandler& writeHandler; 
};

} // namespace app::api::http::handlers