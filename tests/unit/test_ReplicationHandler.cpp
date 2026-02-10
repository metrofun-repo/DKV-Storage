#include <gtest/gtest.h>

#include "tests/mock/MockRequest.h"
#include "tests/mock/MockResponse.h"

#include "storage/KeyValueStorage.h"
#include "storage/KeyValueService.h"

#include "api/internal/ReplicationHttpHandler.h"

#include "cluster/protocol/ReplicationMessage.h"
#include "cluster/protocol/JsonSerializer.h"

TEST(ReplicationHttpHandlerTest, ReplicationSetValue) {
    KeyValueStorage storage;
    KeyValueService service(storage);
    ReplicationHttpHandler handler(service);

    ReplicationMessage msg { OperationType::Set, "key", "value", 1 };

    MockRequest req;

    req.body = toJson(std::move(msg)).dump();

    MockResponse res;

    handler.handleReplicate(req, res);

    EXPECT_EQ(res.status, 200);
    EXPECT_EQ(res.body, "value");
    EXPECT_EQ(service.get("key"), "value");
}

TEST(ReplicationHttpHandlerTest, ReplicationRemoveValue) {
    KeyValueStorage storage;
    KeyValueService service(storage);
    ReplicationHttpHandler handler(service);

    service.set("key", "value", 1);

    ReplicationMessage msg { OperationType::Remove, "key", "value", 1 };

    MockRequest req;
    req.body = toJson(std::move(msg)).dump();

    MockResponse res;

    handler.handleReplicate(req, res);

    EXPECT_EQ(res.status, 200);
    EXPECT_EQ(res.body, "Value succesfully removed");
    EXPECT_EQ(service.get("key"), std::nullopt);
}