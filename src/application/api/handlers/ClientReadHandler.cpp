#include "ClientReadHandler.h"

#include "application/api/builders/ApiResponseBuilder.h"

namespace app::api::handlers {

using ApiResponseBuilder  = app::api::builders::ApiResponseBuilder;

ClientReadHandler::ClientReadHandler(QueryService& service)
    : BaseOperationHandler()
    , query(service)
{
    registerHandlers();
}

void ClientReadHandler::registerHandlers()
{
    handlers[operation_t::Get] = [&](const request_t& req)
    {
        return ApiResponseBuilder::from(query.get(req));
    };
}

} // namespace app::api::handlers