#include <gtest/gtest.h>
#include "tests/mock/MockHttpServer.h"
#include "store/KeyValueStorage.h"
#include "service/KeyValueService.h"

#include "http/HttpMethodHandler.h"
#include "http/RoutesRegistrar.h"
#include "http/Routes.h"
TEST(RouteRegistar, RegisterPublicRoutes) {
    KeyValueStorage storage;
    KeyValueService service(storage);
    HttpMethodHandler handler(service);
    RoutesRegistrar registrar(handler);

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