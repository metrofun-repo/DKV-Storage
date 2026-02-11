#pragma once

#include "http/HttpServer.h"
#include "api/public/PublicHttpHandler.h"
#include "api/public/PublicRouteRegistrar.h"
#include "api/internal/ReplicationHttpHandler.h"
#include "api/internal/ReplicationRouteRegistrar.h"

#include "storage/KeyValueStorage.h"
#include "storage/KeyValueService.h"
#include "config/AppConfig.h"

#include "cluster/replication/ReplicationClient.h"
#include "cluster/service/ReplicationService.h"

class App
{
    AppConfig cfg;
    HttpServer server;
    KeyValueStorage storage;
    KeyValueService keyValueService;
    
    ReplicationClient replicaClient;
    ReplicationService replicaService; 
    
    PublicHttpHandler publicHandler;
    ReplicationHttpHandler replicaHandler;
    PublicRouteRegistrar routesReg;
    ReplicationRouteRegistrar replicaReg;

    void configureRoutes();
public:
    App(AppConfig config);

    void run();
};