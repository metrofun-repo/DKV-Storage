#pragma once

#include "application/api/handlers/BaseOperationHandler.h"
#include "application/cluster/services/ReplicationApplyService.h"

namespace app::cluster::handlers {

class ReplicationWriteHandler : public app::api::handlers::BaseOperationHandler<app::cluster::types::ReplicationOperationType, 
                                                            cluster::protocol::ReplicationRequest,
                                                            cluster::types::ReplicationApplyResult>
{
    using ReplicationApplyService = app::cluster::services::ReplicationApplyService;
public:
    explicit ReplicationWriteHandler(ReplicationApplyService& service);

protected:
    void registerHandlers() override;

    ReplicationApplyService& applier;
};

} // namespace app::cluster::handlers