#pragma once
#include <chrono>
#include <string>
#include <vector>
#include <shared_mutex>
#include <unordered_map>

#include "domain/cluster/model/NodeInfo.h"

namespace app::cluster::state {

class ClusterState
{
    using NodeInfo = domain::cluster::model::NodeInfo;

    struct NodeStatus
    {
        enum class State { Alive, Suspect, Dead };
        std::chrono::steady_clock::time_point lastHearbeat;
        std::chrono::milliseconds latency { 0 };
        State state { State::Alive };
    };

public:
    explicit ClusterState(const std::string& selfId, const std::vector<NodeInfo>& peers, std::size_t quorum, std::chrono::milliseconds suspect, std::chrono::milliseconds dead);

    void setHeartbeatReceived(const std::string& nodeId);
    void setResponseReceived(const std::string& nodeId, std::chrono::milliseconds latency);
    void setHeartbeatFailed(const std::string& nodeId);

    void updateNodeStates();

    bool isAlive(const std::string& nodeId) const;
    bool isSuspect(const std::string& nodeId) const;
    bool isDead(const std::string& nodeId) const;

    bool quorumHealthy() const;

    std::size_t getQuorumSize() const;
    const std::string& getSelfId() const;
    const std::vector<NodeInfo>& getKnownNodes() const;

private:
    const std::string& selfId;
    const std::vector<NodeInfo>& knownNodes;

    mutable std::shared_mutex mtx;
    std::unordered_map<std::string, NodeStatus> nodes;

    std::size_t quorumSize;
    std::chrono::milliseconds suspectThreshold;
    std::chrono::milliseconds deadThreshold;
};

} // namespace app::cluster::state