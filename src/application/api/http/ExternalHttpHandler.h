#pragma once

#include "infrastructure/http/server/HttpRequest.h"
#include "infrastructure/http/server/HttpResponse.h"

#include "application/storage/services/QueryService.h"
#include "application/cluster/services/ReplicationService.h"

namespace app::api::http {

class ExternalHttpHandler
{
public:
    explicit ExternalHttpHandler(storage::services::QueryService& q, cluster::services::ReplicationService& r);

    void handleRequest_GET(const infra::http::server::HttpRequest& req, infra::http::server::HttpResponse& res);
    void handleRequest_POST(const infra::http::server::HttpRequest& req, infra::http::server::HttpResponse& res);
    void handleRequest_DELETE(const infra::http::server::HttpRequest& req, infra::http::server::HttpResponse& res);

private:

    storage::services::QueryService& query;
    cluster::services::ReplicationService& replication;
};

} // namespace app::api::http::handlers