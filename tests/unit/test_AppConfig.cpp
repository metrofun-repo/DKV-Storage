#include <gtest/gtest.h>
#include "config/AppConfig.h"

TEST(AppConfigTest, setHostAndPort) {
    AppConfig cfg;
    
    cfg.host = "localhost";
    cfg.port = 8080;

    EXPECT_EQ(cfg.host, "localhost");
    EXPECT_EQ(cfg.port, 8080);
}

TEST(AppConfigTest, addPeers) {
    AppConfig cfg;

    for(int i = 0; i < 5; ++i)
    {
        cfg.peers.emplace_back("localhost", 8080 + i);
    }

    ASSERT_FALSE(cfg.peers.empty());
    EXPECT_EQ(cfg.peers[0].port, 8080);
    EXPECT_EQ(cfg.peers[4].port, 8084);
}