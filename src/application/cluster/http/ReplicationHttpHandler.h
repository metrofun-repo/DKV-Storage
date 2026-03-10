#pragma once
#include <unordered_map>
#include "infrastructure/http/server/HttpRequest.h"
#include "infrastructure/http/server/HttpResponse.h"

#include "application/cluster/handlers/ReplicationWriteHandler.h"

namespace app::cluster::http {

class ReplicationHttpHandler
{
    using HttpRequest  = infra::http::server::HttpRequest;
    using HttpResponse = infra::http::server::HttpResponse;

    using ReplicationWriteHandler = app::cluster::handlers::ReplicationWriteHandler;    
public:
    ReplicationHttpHandler(ReplicationWriteHandler& service);

    void handleReplicate(const HttpRequest& req, HttpResponse& res);

private:
    ReplicationWriteHandler& writeHandler;
};

} // namespace app::cluster::http