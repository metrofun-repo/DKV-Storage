#include <gtest/gtest.h>
#include "storage/KeyValueStorage.h"

TEST(KeyValueStorageTest, PutAndGet) {
    KeyValueStorage cache;
    cache.put("key", "value", 1);

    auto result = cache.get("key");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->value, "value");
    EXPECT_EQ(result->timestamp, 1);
}

TEST(KeyValueStorageTest, GetMisingKey) {
    KeyValueStorage cache;

    auto result = cache.get("key");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result, std::nullopt);
}

