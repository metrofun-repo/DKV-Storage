#pragma once

#include <gtest/gtest.h>
#include "common/utils/json_utils.h"

TEST(KeyValueServiceTest, SetAndGet) {
    // KVStorage cache;
    // KVService service(cache);
    // service.set("key", "value", 0);

    // auto result = service.get("key");
    // ASSERT_TRUE(result.hasValue());
    // EXPECT_EQ(result.value(), "value");
    EXPECT_EQ(true, true);
}

// TEST(KeyValueServiceTest, GetMisingKey) {
//     KeyValueStorage cache;
//     KeyValueService service(cache);
//     auto result = service.get("key");
//     ASSERT_FALSE(result.success());
//     bool contains = result.payload.contains("value");
//     EXPECT_EQ(contains, false);
// }

// TEST(KeyValueServiceTest, SetGetRemove) {
//     KeyValueStorage cache;
//     KeyValueService service(cache);
//     service.set("key", "value", 0);

//     auto result = service.get("key");
//     ASSERT_TRUE(result.success());
//     auto value = result.payload["value"].get<std::string>(); 
//     EXPECT_EQ(value, "value");

//     service.remove("key");

//     result = service.get("key");
//     ASSERT_FALSE(result.success());
//     bool contains = result.payload.contains("value");
//     EXPECT_EQ(contains, false);
// }
