#pragma once

#include "error/ReplicationError.h"
#include "domain/cluster/model/NodeInfo.h"

#include "application/types/StorageTypes.h"
#include "application/api/requests/ClientRequest.h"
#include "application/cluster/types/ReplicationResult.h"
#include "application/cluster/protocol/ReplicationRequest.h"

#include "infrastructure/transport/senders/ReplicationSender.h"
#include "infrastructure/transport/error/TransportError.h"

namespace app::cluster::services {

class ReplicatorService
{   
    using Key            = app::types::Key;
    using Value          = app::types::Value;
    using StorageService = app::types::StorageService;

    using ReplicationSender  = infra::transport::senders::ReplicationSender;

    using ClientRequest      = app::api::dto::ClientRequest;

    using ReplicationError   = error::ReplicationError;
    using ReplicationRequest = app::cluster::protocol::ReplicationRequest;
    using NodeInfo           = domain::cluster::model::NodeInfo;
    using FanoutResult       = app::cluster::protocol::FanoutResult;     
    using ReplicationResult  = app::cluster::types::ReplicationResult;

    using TransportErrorCode = infra::transport::error::TransportErrorCode;

public:
    ReplicatorService(StorageService& service, ReplicationSender& repSend, const NodeInfo& self, const std::vector<NodeInfo>& nodes);

    ReplicationResult set(const ClientRequest& req);
    ReplicationResult remove(const ClientRequest& req);

private:
    ReplicationError fromTransport(TransportErrorCode code) const;
    FanoutResult fanout(const ReplicationRequest& req) const;
    ReplicationResult quorumReached(const FanoutResult& fanout) const;

    StorageService& domain;
    ReplicationSender& sender;
    const NodeInfo& selfNode;
    const std::vector<NodeInfo>& clusterNodes;
};

} // namespace app::cluster::services