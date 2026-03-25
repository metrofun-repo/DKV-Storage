#pragma once

#include "domain/storage/error/StorageError.h"
#include "application/cluster/protocol/ClusterError.h"
#include "domain/replication/ReplicationFanoutResult.h"

namespace app::cluster::types {

struct ReplicationResult
{
    using FanoutResult = domain::replication::ReplicationFanoutResult;

    using StorageError = domain::storage::error::StorageError;
    using ReplicationError = domain::replication::error::ReplicationError;

    using LocalApplyResult = core::types::Expected<void, StorageError>;
    using ReplicationApply = core::types::Expected<void, ReplicationError>;

    LocalApplyResult localApply;
    ReplicationApply replicaApply;
    FanoutResult fanout;

    bool isSuccess() const { return localApply.hasValue() && replicaApply.hasValue(); }
    bool isLocalFailure() const { return !localApply.hasValue(); }
    bool isReplicationFailure() const { return !replicaApply.hasValue(); }

    static ReplicationResult makeFailure(StorageError local)
    {
        return { LocalApplyResult::makeFailure(std::move(local)), ReplicationApply::makeSuccess(), {} };
    }

    static ReplicationResult makeFailure(ReplicationError rep, FanoutResult fan)
    {
        return { LocalApplyResult::makeSuccess(), ReplicationApply::makeFailure(std::move(rep)), fan };
    }

    static ReplicationResult makeSuccess(FanoutResult fan)
    {
        return { LocalApplyResult::makeSuccess(), ReplicationApply::makeSuccess(), fan };
    }
};

} // namespace app::cluster::types