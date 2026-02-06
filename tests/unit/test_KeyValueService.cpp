#pragma once

#include <gtest/gtest.h>
#include <store/KeyValueStorage.h>
#include <service/KeyValueService.h>

TEST(KeyValueServiceTest, SetAndGet) {
    KeyValueStorage cache;
    KeyValueService service(cache);
    service.set("key", "value");

    auto result = service.get("key");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "value");
}

TEST(KeyValueServiceTest, GetMisingKey) {
    KeyValueStorage cache;
    KeyValueService service(cache);
    auto result = service.get("key");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result, std::nullopt);
}

TEST(KeyValueServiceTest, SetGetRemove) {
    KeyValueStorage cache;
    KeyValueService service(cache);
    service.set("key", "value");

    auto result = service.get("key");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "value");

    service.remove("key");

    result = service.get("key");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result, std::nullopt);
}
