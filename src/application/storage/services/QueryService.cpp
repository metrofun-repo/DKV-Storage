#include "QueryService.h"

#include "error/AppError.h"
#include "application/api/builders/ExternalResponseBuilder.h"
#include "application/api/validation/ExternalRequestValidator.h"

namespace app::storage::services {

using ExternalResponseBuilder  = api::builders::ExternalResponseBuilder;
using ExternalRequestValidator = api::validation::ExternalRequestValidator;

using QueryResult = core::types::Expected<app::types::VersionedValue, error::AppError>;

QueryService::QueryService(app::types::StorageService& service)
    : storage(service)
{}

app::api::dto::ExternalResponse QueryService::get(const api::dto::ExternalRequest& req) const
{
    auto valid = ExternalRequestValidator::validate(req);
    if(!valid.hasValue())
    {
        return ExternalResponseBuilder::from(
            QueryResult::makeFailure(error::AppError { 
                error::AppErrorCode::InvalidRequest,
                valid.error().message
            })
        );
    }

    auto getRes = storage.get(req.key);
    if(!getRes.hasValue())
    {
        return ExternalResponseBuilder::from(
            QueryResult::makeFailure(error::AppError { 
                error::AppErrorCode::StorageFailure,
                getRes.error().message
            })
        );
    }

    const app::types::VersionedValue& value = getRes.value();

    if(value.isTombstone())
    {
        return ExternalResponseBuilder::from(
            QueryResult::makeFailure(error::AppError { 
                error::AppErrorCode::KeyNotFound,
                "Key not found"
            })
        );        
    }

    return ExternalResponseBuilder::from(QueryResult::makeSuccess(value));
}

} // namespace app::storage::services