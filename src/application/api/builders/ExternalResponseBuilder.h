#pragma once

#include "error/AppError.h"
#include "application/types/KeyValueTypes.h"
#include "application/api/responses/ExternalResponse.h"

namespace app::api::builders {

struct ExternalResponseBuilder
{
    using QueryResult = core::types::Expected<app::types::VersionedValue, error::AppError>;
    using ReplicationResult = core::types::Expected<void, error::AppError>;

    static api::dto::ExternalResponse from(const QueryResult& result);
    static api::dto::ExternalResponse from(const ReplicationResult& result);
private:
    static api::dto::ExternalResponse mapAppError(const error::AppError& error);
};

} // namespace app::api::builders