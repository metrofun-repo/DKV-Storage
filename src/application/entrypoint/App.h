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
    HttpReplicationSender replicaSender;

    Storage        storage;
    StorageService storageService;
    
    QueryService   queryService;
    
    ReplicatorService replicatorService;
    ReplicationApplyService applyService; 

    ClientReadHandler clientReadHandler;
    ClientWriteHandler clientWriteHandler;

    ReplicationWriteHandler replicaWriteHandler;

    PublicHttpHandler publicHandler;
    ReplicationHttpHandler replicaHandler;
    HttpRequestRouter requestRouter;

public:
    App(AppConfig config);

    void run();
};

} // namespace app::entrypoint