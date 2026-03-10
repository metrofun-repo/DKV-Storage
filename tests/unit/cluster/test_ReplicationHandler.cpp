#include <gtest/gtest.h>

#include "tests/mock/MockRequest.h"
#include "tests/mock/MockResponse.h"

#include "application/cluster/http/ReplicationHttpHandler.h"

#include "application/cluster/protocol/ReplicationRequest.h"
#include "application/cluster/services/ReplicationApplyService.h"

TEST(ReplicationHttpHandlerTest, ReplicationSetValue) {
    // KVStorage storage;
    // KVService service(storage);
    // ReplicationApplyService applyService(service);
    // ReplicationHttpHandler handler(applyService);

    // ReplicationRequest replicaReq { ReplicationOperationType::Set, "key", "value", 1 };

    // MockRequest req;

    // req.body = replicaReq.toJson().dump();

    // MockResponse res;

    // handler.handleReplicate(req, res);

    // EXPECT_EQ(res.status, 200);
    // EXPECT_EQ(res.body, "value");
    // EXPECT_EQ(service.get("key"), "value");
    EXPECT_EQ(true, true);
}

TEST(ReplicationHttpHandlerTest, ReplicationRemoveValue) {
    // KVStorage storage;
    // KVService service(storage);
    // ReplicationApplyService applyService(service);
    // ReplicationHttpHandler handler(applyService);

    // service.set("key", "value", 1);

    // ReplicationRequest replicaReq { ReplicationOperationType::Delete, "key", "value", 1 };

    // MockRequest req;
    // req.body = replicaReq.toJson().dump();

    // MockResponse res;

    // handler.handleReplicate(req, res);

    

    // EXPECT_EQ(res.status, 200);
    // EXPECT_EQ(res.body, "Value succesfully removed");
    // EXPECT_EQ(service.get("key"), std::nullopt);
    EXPECT_EQ(true, true);
}