#pragma once

#include "error/AppError.h"
#include "application/types/KeyValueTypes.h"
#include "application/api/responses/ClientResponse.h"
#include "application/cluster/types/ReplicationResult.h"
#include "application/cluster/types/ReplicationApplyResult.h"

#include "domain/storage/model/VersionedValue.h"

namespace app::api::builders {

struct ApiResponseBuilder
{
    using AppError = error::AppError;
    using VersionedValue = domain::storage::model::VersionedValue<app::types::Value>;

    using ClientResponse = app::api::dto::ClientResponse;
    using ReplicationResult = app::cluster::types::ReplicationResult;
    using ReplicationApplyResult = app::cluster::types::ReplicationApplyResult;

    using QueryResult = core::types::Expected<VersionedValue, AppError>;

    static ClientResponse from(const QueryResult& result);
    static ClientResponse from(const ReplicationResult& result);
    static ClientResponse from(const ReplicationApplyResult& result);
};

} // namespace app::api::builders