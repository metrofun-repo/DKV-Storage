#include <gtest/gtest.h>

#include "storage/KeyValueStorage.h"
#include "storage/KeyValueService.h"
#include "api/public/PublicHttpHandler.h"

#include "tests/mock/MockRequest.h"
#include "tests/mock/MockResponse.h"
#include "tests/mock/MockReplicationClient.h"

#include "cluster/service/ReplicationService.h"

TEST(PublicHttpHandlerTest, GetReturnsValueIfExists) {
    KeyValueStorage storage;
    KeyValueService keyValueService(storage);
    MockReplicationClient client;
    ReplicationService replicaService(keyValueService, client);
    PublicHttpHandler handler(keyValueService, replicaService);

    keyValueService.set("key", "value", 0);

    MockRequest req;
    req.params["key"] = "key";

    MockResponse res;

    handler.handleGet(req, res);

    EXPECT_EQ(res.status, 200);
    EXPECT_EQ(res.body, "value");
}

TEST(PublicHttpHandlerTest, GetReturns404IfNotFound) {
    KeyValueStorage storage;
    KeyValueService keyValueService(storage);
    MockReplicationClient client;
    ReplicationService replicaService(keyValueService, client);
    PublicHttpHandler handler(keyValueService, replicaService);

    MockRequest req;
    req.params["key"] = "missing";

    MockResponse res;

    handler.handleGet(req, res);

    EXPECT_EQ(res.status, 404);
    EXPECT_EQ(res.body, "No value found in storage");
}

TEST(PublicHttpHandlerTest, PostStoresValue) {
    KeyValueStorage storage;
    KeyValueService keyValueService(storage);
    MockReplicationClient client;
    ReplicationService replicaService(keyValueService, client);
    PublicHttpHandler handler(keyValueService, replicaService);

    MockRequest req;
    req.params["key"] = "abc";
    req.body = "value007";

    MockResponse res;

    handler.handleSet(req, res);

    EXPECT_EQ(res.status, 200);
    EXPECT_EQ(keyValueService.get("abc"), "value007");    
}