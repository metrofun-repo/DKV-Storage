#include <gtest/gtest.h>

#include "tests/mock/MockHttpServer.h"
#include "tests/mock/MockReplicationClient.h"

#include "storage/KeyValueStorage.h"
#include "storage/KeyValueService.h"

#include "api/public/PublicHttpHandler.h"
#include "api/public/PublicRouteRegistrar.h"
#include "api/public/Routes.h"

#include "cluster/service/ReplicationService.h"

TEST(RouteRegistrarTest, RegisterPublicRoutes) {
    KeyValueStorage storage;
    KeyValueService service(storage);
    MockReplicationClient client;
    ReplicationService replicaService(service, client);
    PublicHttpHandler handler(service, replicaService);
    PublicRouteRegistrar registrar(handler);

    MockHttpServer server;

    registrar.registerPublicRoutes(server);

    EXPECT_EQ(server.routes.size(), 3);
    EXPECT_EQ(server.routes[0].method, "POST");
    EXPECT_EQ(server.routes[0].path, Routes::Public::SET);
    EXPECT_EQ(server.routes[1].method, "GET");
    EXPECT_EQ(server.routes[1].path, Routes::Public::GET);
    EXPECT_EQ(server.routes[2].method, "DELETE");
    EXPECT_EQ(server.routes[2].path, Routes::Public::REMOVE);
}