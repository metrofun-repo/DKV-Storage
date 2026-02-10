#include <gtest/gtest.h>

#include "tests/mock/MockHttpServer.h"

#include "storage/KeyValueStorage.h"
#include "storage/KeyValueService.h"

#include "api/internal/Routes.h"
#include "api/internal/ReplicationHttpHandler.h"
#include "api/internal/ReplicationRouteRegistrar.h"

TEST(ReplicationRouteRegistarTest, RegisterReplicationRoutes) {
    KeyValueStorage storage;
    KeyValueService service(storage);

    ReplicationHttpHandler handler(service);
    ReplicationRouteRegistrar registrar(handler);

    MockHttpServer server;

    registrar.registerReplicationRoutes(server);

    EXPECT_EQ(server.routes.size(), 1);
    EXPECT_EQ(server.routes[0].method, "POST");
    EXPECT_EQ(server.routes[0].path, ReplicationRoutes::REPLICATE);
}