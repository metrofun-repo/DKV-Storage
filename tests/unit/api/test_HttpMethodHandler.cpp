#include <gtest/gtest.h>

// #include "tests/mock/MockHttpServer.h"

// #include "storage/KeyValueStorage.h"
// #include "storage/KeyValueService.h"
// #include "api/handler/PublicHttpHandler.h"

// #include "tests/mock/MockRequest.h"
// #include "tests/mock/MockResponse.h"
// #include "tests/mock/MockReplicationSender.h"

// #include "cluster/service/ReplicatorService.h"

// TEST(PublicHttpHandlerTest, GetReturnsValueIfExists) {
//     KeyValueStorage storage;
//     KeyValueService keyValueService(storage);
//     QueryService queryService(keyValueService);
//     MockHttpServer server;
//     MockReplicationSender sender;
//     ReplicatorService replicatorService(keyValueService, sender);
//     PublicHttpHandler handler(queryService, replicatorService);

//     keyValueService.set("key", "value", 0);

//     MockRequest req;
//     req.params["key"] = "key";

//     MockResponse res;

//     handler.handleRequest(req, res);

//     EXPECT_EQ(res.status, 200);
//     EXPECT_EQ(res.body, "value");
// }

// TEST(PublicHttpHandlerTest, GetReturns404IfNotFound) {
//     KeyValueStorage storage;
//     KeyValueService keyValueService(storage);
//     QueryService queryService(keyValueService);
//     MockHttpServer server;
//     MockReplicationSender sender;
//     ReplicatorService replicatorService(keyValueService, sender);
//     PublicHttpHandler handler(queryService, replicatorService);

//     MockRequest req;
//     req.params["key"] = "missing";

//     MockResponse res;

//     handler.handleRequest(req, res);

//     EXPECT_EQ(res.status, 404);
//     EXPECT_EQ(res.body, "No value found in storage");
// }

// TEST(PublicHttpHandlerTest, PostStoresValue) {
//     KeyValueStorage storage;
//     KeyValueService keyValueService(storage);
//     QueryService queryService(keyValueService);
//     MockHttpServer server;
//     MockReplicationSender sender;
//     ReplicatorService replicatorService(keyValueService, sender);
//     PublicHttpHandler handler(queryService, replicatorService);

//     MockRequest req;
//     req.params["key"] = "abc";
//     req.body = "value007";

//     MockResponse res;

//     handler.handleRequest(req, res);

//     EXPECT_EQ(res.status, 200);
//     EXPECT_EQ(keyValueService.get("abc"), "value007");    
// }