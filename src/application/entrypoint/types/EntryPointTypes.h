#pragma once

#include "application/types/StorageTypes.h"
#include "application/storage/services/QueryService.h"
#include "infrastructure/http/routing/HttpRequestRouter.h"

#include "domain/storage/services/KeyValueService.h"

#include "application/cluster/services/ReplicationApplyService.h"
#include "application/cluster/services/ReplicatorService.h"

#include "infrastructure/http/adapters/http_httplib/server/HttplibServer.h"
#include "infrastructure/http/adapters/http_httplib/client/HttplibClient.h"
#include "infrastructure/transport/senders/HttpReplicationSender.h"

namespace app::entrypoint::types {

    using HttpClient            = infra::http::adapters::httplib::client::HttplibClient;
    using HttpServer            = infra::http::adapters::httplib::server::HttplibServer;
    using HttpReplicationSender = infra::transport::senders::HttpReplicationSender;
    using HttpRequestRouter     = infra::http::routing::HttpRequestRouter;

    using Storage               = app::types::Storage;
    using StorageService        = app::types::StorageService;

    using QueryService            = app::storage::services::QueryService;

    using ReplicatorService       = app::cluster::services::ReplicatorService;
    using ReplicationApplyService = app::cluster::services::ReplicationApplyService;

    using ClientReadHandler       = app::api::handlers::ClientReadHandler;
    using ClientWriteHandler      = app::api::handlers::ClientWriteHandler;

    using ReplicationWriteHandler = app::cluster::handlers::ReplicationWriteHandler;

    using PublicHttpHandler       = app::api::http::PublicHttpHandler;
    using ReplicationHttpHandler  = app::cluster::http::ReplicationHttpHandler;

} //namespace app::entrypoint::types