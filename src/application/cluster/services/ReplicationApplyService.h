#pragma once

#include "application/types/StorageTypes.h"

#include "application/cluster/protocol/ReplicationRequest.h"
#include "application/cluster/types/ReplicationApplyResult.h"

namespace app::cluster::services {

class ReplicationApplyService
{
    using StorageService         = app::types::StorageService;
    using ReplicationRequest     = app::cluster::protocol::ReplicationRequest;
    using ReplicationApplyResult = app::cluster::types::ReplicationApplyResult;

public:
    explicit ReplicationApplyService(StorageService& kvs);
    ReplicationApplyResult applySet(const ReplicationRequest& req);
    ReplicationApplyResult applyRemove(const ReplicationRequest& req);

private:
    StorageService& storage;
};

} // namespace app::cluster::services