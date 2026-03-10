#include "ClientWriteHandler.h"

#include "application/api/builders/ApiResponseBuilder.h"

namespace app::api::handlers {

using ApiResponseBuilder  = app::api::builders::ApiResponseBuilder;

ClientWriteHandler::ClientWriteHandler(ReplicatorService& service)
    : BaseOperationHandler()
    , replicator(service)
{
    registerHandlers();
}

void ClientWriteHandler::registerHandlers()
{
    handlers[operation_t::Set] = [&](const request_t& req)
    {
        return ApiResponseBuilder::from(replicator.set(req));
    };
    handlers[operation_t::Delete] = [&](const request_t& req)
    {
        return ApiResponseBuilder::from(replicator.remove(req));
    };
}

} // namespace app::api::handlers