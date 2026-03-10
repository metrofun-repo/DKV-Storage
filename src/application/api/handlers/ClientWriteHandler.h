#pragma once

#include "BaseOperationHandler.h"
#include "application/cluster/services/ReplicatorService.h"

namespace app::api::handlers {

class ClientWriteHandler : public BaseOperationHandler<app::api::types::ClientOperationType, 
                                                      app::api::dto::ClientRequest,
                                                      app::api::dto::ClientResponse>
{
    using ReplicatorService = app::cluster::services::ReplicatorService;
public:
    explicit ClientWriteHandler(ReplicatorService& service);

private:
    void registerHandlers() override;

    ReplicatorService& replicator;
};

} // namespace app::api::handlers