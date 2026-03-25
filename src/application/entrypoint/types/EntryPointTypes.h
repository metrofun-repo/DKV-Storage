#pragma once

#include "application/types/StorageTypes.h"
#include "application/storage/services/QueryService.h"

#include "application/cluster/services/ReplicationService.h"
#include "application/cluster/services/HeartbeatService.h"
#include "application/cluster/heartbeat/HeartbeatLoop.h"

#include "infrastructure/http/routing/HttpRequestRouter.h"
#include "infrastructure/http/adapters/http_httplib/server/HttplibServer.h"
#include "infrastructure/http/adapters/http_httplib/client/HttplibClient.h"
#include "infrastructure/transport/senders/HttpClusterSender.h"
#include "infrastructure/storage/CompactionLoop.h"

namespace app::entrypoint::types {

    using HttpClient         = infra::http::adapters::httplib::client::HttplibClient;
    using HttpServer         = infra::http::adapters::httplib::server::HttplibServer;
    using HttpClusterSender  = infra::transport::senders::HttpClusterSender;
    using HttpRequestRouter  = infra::http::routing::HttpRequestRouter;

    using Storage            = app::types::Storage;
    using StorageService     = app::types::StorageService;

    using QueryService       = storage::services::QueryService;

    using ClusterState       = cluster::state::ClusterState;

    using HeartbeatService   = cluster::services::HeartbeatService;
    using ReplicationService = cluster::services::ReplicationService;

    using ExternalHttpHandler = api::http::ExternalHttpHandler;
    using InternalHttpHandler = cluster::http::InternalHttpHandler;

    using HeartbeatLoop  = cluster::heartbeat::HeartbeatLoop;
    using CompactionLoop = infra::storage::CompactionLoop;


} //namespace app::entrypoint::types