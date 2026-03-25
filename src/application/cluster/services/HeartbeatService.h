#pragma once

#include <vector>
#include <thread>
#include <atomic>

#include "domain/cluster/model/NodeInfo.h"
#include "domain/replication/error/HeartbeatError.h"
#include "domain/replication/HeartbeatFanoutResult.h"

#include "application/cluster/state/ClusterState.h"

#include "infrastructure/transport/senders/HttpClusterSender.h"

#include "application/cluster/protocol/InternalRequest.h"
#include "application/cluster/protocol/InternalResponse.h"


namespace app::cluster::services {

class HeartbeatService
{   
public:    
    explicit HeartbeatService(
        state::ClusterState& state,
        infra::transport::senders::HttpClusterSender& sender);

    protocol::InternalResponse apply(const protocol::InternalRequest& req);

    void sendHeartbeat();
    void tick();

private:
    state::ClusterState& clusterState;
    infra::transport::senders::HttpClusterSender& sender;
};

} // namespace app::cluster::services