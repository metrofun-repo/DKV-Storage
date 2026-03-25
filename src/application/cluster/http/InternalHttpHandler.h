#pragma once
#include "infrastructure/http/server/HttpRequest.h"
#include "infrastructure/http/server/HttpResponse.h"
#include "application/cluster/services/HeartbeatService.h"
#include "application/cluster/services/ReplicationService.h"

namespace app::cluster::http {

class InternalHttpHandler
{
public:
    explicit InternalHttpHandler(
        services::HeartbeatService& hb,
        services::ReplicationService& rp);

    void handleRequest(
        const infra::http::server::HttpRequest& req,
        infra::http::server::HttpResponse& res);

private:
    services::HeartbeatService& hbService;
    services::ReplicationService& rpService;
};

} // namespace app::cluster::http