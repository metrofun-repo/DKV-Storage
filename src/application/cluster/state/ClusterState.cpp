#include "ClusterState.h"
#include <iostream>
namespace app::cluster::state {

ClusterState::ClusterState(const std::string& selfId, const std::vector<NodeInfo>& peers, std::size_t quorum, std::chrono::milliseconds suspect, std::chrono::milliseconds dead)
    : selfId(selfId)
    , knownNodes(peers)
    , quorumSize(quorum)
    , suspectThreshold(suspect)
    , deadThreshold(dead)
{
    for(auto& n : peers)
    {
        nodes.emplace(n.nodeId, NodeStatus{});
    }
}

void ClusterState::setHeartbeatReceived(const std::string& nodeId)
{
    std::unique_lock lock { mtx };
    auto& status = nodes[nodeId];
    status.lastHearbeat = std::chrono::steady_clock::now();
}

void ClusterState::setResponseReceived(const std::string& nodeId, std::chrono::milliseconds latency)
{
    std::unique_lock lock { mtx };
    nodes[nodeId].latency = latency;
}
void ClusterState::setHeartbeatFailed(const std::string& nodeId)
{
    // auto& status = hb[nodeId];
    // ++status.failedHeartbeats;

    // if(status.failedHeartbeats >= failureThreshold)
    //     alive.erase(nodeId);
}

void ClusterState::updateNodeStates()
{
    using namespace std::chrono;
    auto now = steady_clock::now();

    // std::cout << "-----------------------------------------" << std::endl;
    std::unique_lock lock { mtx };
    for(auto& [node, status] : nodes)
    {
        auto elapsed = now - status.lastHearbeat;
        if(elapsed >= deadThreshold)
        {
            status.state = NodeStatus::State::Dead;
        }
        else if(elapsed >= suspectThreshold)
        {
            status.state = NodeStatus::State::Suspect;
        }
        else
        {
            status.state = NodeStatus::State::Alive;
        }
        // std::cout << "[" << selfId << "] " << __func__ << "node: " << node << " status: " << static_cast<int>(status.state) << std::endl;
    }
}

bool ClusterState::isAlive(const std::string& nodeId) const
{
    std::shared_lock lock { mtx };
    if(auto it = nodes.find(nodeId); it != nodes.end())
    {
        return it->second.state == NodeStatus::State::Alive;
    }
    return false;    
}

bool ClusterState::isSuspect(const std::string& nodeId) const
{
    std::shared_lock lock { mtx };
    if(auto it = nodes.find(nodeId); it != nodes.end())
    {
        return it->second.state == NodeStatus::State::Suspect;
    }
    return false;    
}

bool ClusterState::isDead(const std::string& nodeId) const
{
    std::shared_lock lock { mtx };
    if(auto it = nodes.find(nodeId); it != nodes.end())
    {
        return it->second.state == NodeStatus::State::Dead;
    }
    return false;
}

bool ClusterState::quorumHealthy() const
{
    std::shared_lock lock { mtx };
    std::size_t alive = 1;
    for(auto& [node, status] : nodes)
    {
        if(status.state == NodeStatus::State::Alive)
            ++alive;
    }

    return alive >= quorumSize;
}

const std::string& ClusterState::getSelfId() const
{
    return selfId;
}

const std::vector<ClusterState::NodeInfo>& ClusterState::getKnownNodes() const
{ 
    return knownNodes;
} 

std::size_t ClusterState::getQuorumSize() const
{
    return quorumSize;
}

}