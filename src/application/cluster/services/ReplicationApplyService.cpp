#include "ReplicationApplyService.h"

#include "application/cluster/validation/ReplicationRequestValidator.h"

namespace app::cluster::services {

using cluster::validation::ReplicationRequestValidator;

ReplicationApplyService::ReplicationApplyService(StorageService& kvs)
    : storage(kvs)
{}

ReplicationApplyService::ReplicationApplyResult ReplicationApplyService::applySet(const ReplicationRequest& req)
{
    auto validation = ReplicationRequestValidator::validate(req);
    if(!validation.hasValue())
    {
        return { false, error::ReplicationError::InvalidRequest };
    }
    auto applyResult = storage.set(req.key, req.value.value(), req.timestamp);
    if(!applyResult.hasValue())
    {
        return { false, error::ReplicationError::RemoteApplyFailed };
    }
    return { true, error::ReplicationError::None };
}

ReplicationApplyService::ReplicationApplyResult ReplicationApplyService::applyRemove(const ReplicationRequest& req)
{
    auto validation = ReplicationRequestValidator::validate(req);
    if(!validation.hasValue())
    {
        return { false, error::ReplicationError::InvalidRequest };
    }
    auto applyResult = storage.remove(req.key);
    if(!applyResult.hasValue())
    {
        return { false, error::ReplicationError::RemoteApplyFailed };
    }
    return { true, error::ReplicationError::None };
}

} // namespace app::cluster::services