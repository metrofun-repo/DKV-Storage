#include <gtest/gtest.h>
#include "application/entrypoint/AppConfig.h"

using namespace app::entrypoint;

TEST(AppConfigTest, setHostAndPort) {
    AppConfig cfg;
    
    cfg.nodeInfo.nodeId = "nodeID";
    cfg.nodeInfo.host = "localhost";
    cfg.nodeInfo.port = 8080;

    EXPECT_EQ(cfg.nodeInfo.nodeId, "nodeID");
    EXPECT_EQ(cfg.nodeInfo.host, "localhost");
    EXPECT_EQ(cfg.nodeInfo.port, 8080);
}

TEST(AppConfigTest, addPeers) {
    AppConfig cfg;

    for(int i = 0; i < 5; ++i)
    {
        cfg.nodes.emplace_back(std::string("node") + std::to_string(i),"localhost", 8080 + i);
    }

    ASSERT_FALSE(cfg.nodes.empty());
    EXPECT_EQ(cfg.nodes[0].port, 8080);
    EXPECT_EQ(cfg.nodes[4].port, 8084);
}