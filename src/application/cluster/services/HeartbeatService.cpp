#include "HeartbeatService.h"

#include <iostream>

#include "application/cluster/protocol/HeartbeatPayload.h"
#include "application/cluster/builders/InternalResponseBuilder.h"

#include "domain/replication/error/HeartbeatError.h"

namespace app::cluster::services {

using InternalResponseBuilder = builders::InternalResponseBuilder;
using InternalResponse        = protocol::InternalResponse;
using InternalRequest         = protocol::InternalRequest;

using HeartbeatResponsePayload = domain::replication::HeartbeatResponsePayload;
using HeartbeatErrorCode       = domain::replication::error::HeartbeatErrorCode;
using HeartbeatError           = domain::replication::error::HeartbeatError;

////////////////////////////////////////////////////////
using HttpSender   = infra::transport::senders::HttpClusterSender;
using ClusterState = state::ClusterState;

using HeartbeatPayload = protocol::HeartbeatPayload;

HeartbeatService::HeartbeatService(ClusterState& state, HttpSender& sender)
    : clusterState(state)
    , sender(sender)
{}

InternalResponse HeartbeatService::apply(const InternalRequest& req)
{
    const auto& payload = std::get<HeartbeatPayload>(req.payload);
    // std::cout << "HB received: " << payload.nodeId << ":" << payload.timestamp << std::endl;
    clusterState.setHeartbeatReceived(payload.nodeId);
    // HandleResult::makeFailure(HbError {
    //     HeartbeatErrorCode::ApplyFailed,
    //     "Heartbeat apply failed"
    // });
    return InternalResponseBuilder::from(HeartbeatResponsePayload { true });
}

void HeartbeatService::sendHeartbeat()
{
    using namespace std::chrono;

    for(auto& node : clusterState.getKnownNodes())
    {
        if(!clusterState.isDead(node.nodeId)) continue;

        auto now = steady_clock::now();
        auto ts = duration_cast<milliseconds>(now.time_since_epoch()).count();
        InternalRequest req { InternalRequest::Type::Heartbeat, HeartbeatPayload { clusterState.getSelfId(), ts } };

        auto sendTime = steady_clock::now();
        
        auto result = sender.send(req, node);
        
        auto latency = duration_cast<milliseconds>(steady_clock::now() - sendTime);

        if(!result.hasValue())
        {
            clusterState.setHeartbeatFailed(node.nodeId);
            continue;
        }

        auto& hbResponse = std::get<HeartbeatResponsePayload>(result.value().payload);
        if(!hbResponse.applied)
        {
            clusterState.setHeartbeatFailed(node.nodeId);
            continue;            
        }
        
        clusterState.setResponseReceived(node.nodeId, latency);            
    }
}

void HeartbeatService::tick()
{
    sendHeartbeat();
    clusterState.updateNodeStates();
}

}
