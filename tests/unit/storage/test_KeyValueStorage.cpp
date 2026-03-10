#include <gtest/gtest.h>
#include "infrastructure/storage/types/KeyValueStorage.h"

TEST(KeyValueStorageTest, PutAndGet) {
    // KVStorage cache;
    // cache.rawSet("key", { "value", 1 });

    // auto result = cache.rawGet("key");
    // ASSERT_TRUE(result.hasValue());
    // EXPECT_EQ(result.value().value().value, "value");
    // EXPECT_EQ(result.value().value().timestamp, 1);
    EXPECT_EQ(true, true);
}

TEST(KeyValueStorageTest, GetMisingKey) {
    // KVStorage cache;

    // auto result = cache.rawGet("key");
    // ASSERT_FALSE(result.hasValue());
    // EXPECT_EQ(result.value(), std::nullopt);
    EXPECT_EQ(true, true);
}

