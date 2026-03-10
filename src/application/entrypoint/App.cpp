#include "App.h"

namespace app::entrypoint {

App::App(AppConfig config)
    : cfg(std::move(config))
    , client()
    , server(cfg.nodeInfo)
    , replicaSender(client)
    , storage()
    , storageService(storage)
    , queryService(storageService)
    , replicatorService(storageService, replicaSender, cfg.nodeInfo, cfg.nodes)
    , applyService(storageService)
    , clientReadHandler(queryService)
    , clientWriteHandler(replicatorService)
    , replicaWriteHandler(applyService)
    , publicHandler(clientReadHandler, clientWriteHandler)
    , replicaHandler(replicaWriteHandler)
    , requestRouter(server, publicHandler, replicaHandler)
{}

void App::run()
{
    server.start();
}

} // namespace app::entrypoint