#include "ReplicationWriteHandler.h"

namespace app::cluster::handlers {

ReplicationWriteHandler::ReplicationWriteHandler(ReplicationApplyService& service)
    : BaseOperationHandler()
    , applier(service)
{
    registerHandlers();
}

void ReplicationWriteHandler::registerHandlers()
{
    handlers[operation_t::Set] = [&](const request_t& req)
    {
        return applier.applySet(req);
    };
    handlers[operation_t::Delete] = [&](const request_t& req)
    {
        return applier.applyRemove(req);
    };
}

} // namespace app::cluster::handlers