#pragma once

#include "error/AppError.h"
#include "application/types/StorageTypes.h"
#include "application/api/requests/ExternalRequest.h"
#include "application/api/responses/ExternalResponse.h"

#include "application/cluster/state/ClusterState.h"
#include "application/cluster/protocol/ReplicationPayload.h"
#include "application/cluster/protocol/InternalRequest.h"
#include "application/cluster/protocol/InternalResponse.h"

#include "domain/replication/ReplicationFanoutResult.h"
#include "domain/replication/ReplicationResponsePayload.h"

#include "infrastructure/transport/senders/HttpClusterSender.h"

namespace app::cluster::services {

class ReplicationService
{
public:
    explicit ReplicationService(
        state::ClusterState& state,
        app::types::StorageService& storage,
        infra::transport::senders::HttpClusterSender& sender);

    api::dto::ExternalResponse replicate(const api::dto::ExternalRequest& req);
    protocol::InternalResponse apply(const protocol::InternalRequest& req);
private:
    bool quorumReached(const domain::replication::ReplicationFanoutResult& fanout) const;

    domain::replication::ReplicationFanoutResult fanout(const protocol::ReplicationPayload& payload);

    template <typename Fn>
    core::types::Expected<void, error::AppError> replicationOperation(const protocol::ReplicationPayload& payload, Fn&& applyFn);

private:
    app::types::StorageService& storage;
    state::ClusterState& clusterState;
    infra::transport::senders::HttpClusterSender& sender;
};

} // namespace app::cluster::services