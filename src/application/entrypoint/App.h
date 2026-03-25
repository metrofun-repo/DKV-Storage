#pragma once

#include "AppConfig.h"
#include "application/entrypoint/types/EntryPointTypes.h"

namespace app::entrypoint {

using namespace app::entrypoint::types;
class App
{
    AppConfig cfg;

    HttpClient client;
    HttpServer server;
    HttpClusterSender clusterSender;

    Storage        storage;
    StorageService storageService;
    
    QueryService   queryService;

    ClusterState clusterState;
    HeartbeatService hbService;
    ReplicationService rpService;

    ExternalHttpHandler publicHandler;
    InternalHttpHandler clusterHandler;
    HttpRequestRouter requestRouter;

    HeartbeatLoop hbLoop;
    CompactionLoop cmLoop;

public:
    App(AppConfig config);

    void run();
};

} // namespace app::entrypoint