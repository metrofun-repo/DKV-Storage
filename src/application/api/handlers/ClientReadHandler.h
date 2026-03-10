#pragma once

#include "BaseOperationHandler.h"
#include "application/storage/services/QueryService.h"

namespace app::api::handlers {

class ClientReadHandler : public BaseOperationHandler<app::api::types::ClientOperationType,
                                                        app::api::dto::ClientRequest,
                                                        app::api::dto::ClientResponse>
{
    using QueryService = app::storage::services::QueryService;
public:
    explicit ClientReadHandler(QueryService& service);

protected:
    void registerHandlers() override;

    QueryService& query;
};

} // namespace app::api::handlers