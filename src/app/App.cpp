#include "App.h"

App::App(AppConfig config)
    : cfg(std::move(config))
    , server(cfg.host, cfg.port)
    , storage()
    , keyValueService(storage)
    , replicaClient(cfg.peers)
    , replicaService(keyValueService, replicaClient)
    , publicHandler(keyValueService, replicaService)
    , replicaHandler(keyValueService)
    , routesReg(publicHandler)
    , replicaReg(replicaHandler)
{
    configureRoutes();
}

void App::configureRoutes()
{
    routesReg.registerPublicRoutes(server);
    replicaReg.registerReplicationRoutes(server);
}

void App::run()
{
    server.start();
}