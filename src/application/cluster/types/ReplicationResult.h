#pragma once

#include "error/StorageError.h"
#include "error/ReplicationError.h"
#include "application/cluster/protocol/FanoutResult.h"

namespace app::cluster::types {

struct ReplicationResult
{
    using FanoutResult = app::cluster::protocol::FanoutResult;

    using StorageError     = error::StorageError;
    using ReplicationError = error::ReplicationError;

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
        return { LocalApplyResult::makeFailure(local), ReplicationApply::makeSuccess(), {} };
    }

    static ReplicationResult makeFailure(ReplicationError replic, FanoutResult fan)
    {
        return { LocalApplyResult::makeSuccess(), ReplicationApply::makeFailure(replic), fan };
    }

    static ReplicationResult makeSuccess(FanoutResult fan)
    {
        return { LocalApplyResult::makeSuccess(), ReplicationApply::makeSuccess(), fan };
    }
};

} // namespace app::cluster::types