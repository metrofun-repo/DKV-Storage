#include <gtest/gtest.h>

#include "store/KeyValueStorage.h"
#include "service/KeyValueService.h"
#include "http/HttpMethodHandler.h"

#include "tests/mock/MockRequest.h"
#include "tests/mock/MockResponse.h"

TEST(HttpMethodHandlerTest, GetReturnsValueIfExists) {
    KeyValueStorage storage;
    KeyValueService service(storage);
    HttpMethodHandler handler(service);

    service.set("key", "value");

    MockRequest req;
    req.params["key"] = "key";

    MockResponse res;

    handler.handleGet(req, res);

    EXPECT_EQ(res.status, 200);
    EXPECT_EQ(res.body, "value");
}

TEST(HttpMethodHandlerTest, GetReturns404IfNotFound) {
    KeyValueStorage storage;
    KeyValueService service(storage);
    HttpMethodHandler handler(service);

    MockRequest req;
    req.params["key"] = "missing";

    MockResponse res;

    handler.handleGet(req, res);

    EXPECT_EQ(res.status, 404);
    EXPECT_EQ(res.body, "No value found in storage");
}

TEST(HttpMethodHandlerTest, PostStoresValue) {
    KeyValueStorage storage;
    KeyValueService service(storage);
    HttpMethodHandler handler(service);

    MockRequest req;
    req.params["key"] = "abc";
    req.body = "value007";

    MockResponse res;

    handler.handleSet(req, res);

    EXPECT_EQ(res.status, 200);
    EXPECT_EQ(service.get("abc"), "value007");
}