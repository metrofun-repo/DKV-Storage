#include "App.h"

namespace app::entrypoint {

App::App(AppConfig config)
    : cfg(std::move(config))
    , client()
    , server(cfg.nodeInfo)
    , clusterSender(client)
    , storage()
    , storageService(storage)
    , queryService(storageService)
    , clusterState(cfg.nodeInfo.nodeId,
                   cfg.nodes,
                   cfg.quorumThreshold,
                   cfg.suspectThreshold,
                   cfg.deadThreshold)
    , hbService(clusterState, clusterSender)
    , rpService(clusterState, storageService, clusterSender)
    , publicHandler(queryService, rpService)
    , clusterHandler(hbService, rpService)
    , requestRouter(server, publicHandler, clusterHandler)
    , hbLoop(cfg.hbPeriod, hbService)
    , cmLoop(cfg.compactionPeriod, storage)
{}

void App::run()
{
    hbLoop.start();
    server.start();
}

} // namespace app::entrypoint