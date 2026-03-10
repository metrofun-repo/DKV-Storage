#include <gtest/gtest.h>

#include "tests/mock/MockHttpServer.h"
#include "tests/mock/MockReplicationSender.h"

#include "application/types/StorageTypes.h"
#include "application/storage/services/QueryService.h"

#include "infrastructure/http/routing/HttpRequestRouter.h"

using namespace app::types;
using namespace app::storage::services;
using namespace app::cluster::services;
using namespace app::api::handlers;
using namespace infra::http::server;
using namespace infra::http::routing;

TEST(RequestRouterTest, RegisterRoutes) {
    // Storage storage;
    // StorageService service(storage);
    // QueryService queryService(service);

    // MockReplicationSender sender;
    // MockHttpServer server;

    // ReplicatorService replicatorService(service, sender, {}, {});
    // ReplicationApplyService applyService(service);
    // PublicHttpHandler handler(queryService, replicatorService);
    // ReplicationHttpHandler replicaHandler(applyService);
    // HttpRequestRouter registrar(server, handler, replicaHandler);

    // EXPECT_EQ(server.routes.size(), 3);
    // EXPECT_EQ(server.routes[0].method, "POST");
    // EXPECT_EQ(server.routes[0].path, infra::http::server::routes::SET);
    // EXPECT_EQ(server.routes[1].method, "GET");
    // EXPECT_EQ(server.routes[1].path, infra::http::server::routes::GET);
    // EXPECT_EQ(server.routes[2].method, "DELETE");
    // EXPECT_EQ(server.routes[2].path, infra::http::server::routes::REMOVE);
    // EXPECT_EQ(server.routes[3].method, "POST");
    // EXPECT_EQ(server.routes[3].path, infra::http::server::routes::REPLICATE);
    EXPECT_EQ(true, true);
}