#include "QueryService.h"

#include "application/api/validation/ClientRequestValidator.h"

namespace app::storage::services {

using app::api::validation::ClientRequestValidator;

QueryService::QueryService(StorageService& kvService)
    : domain(kvService)
{}

QueryService::Result QueryService::get(const ClientRequest& req) const
{
    auto valid = ClientRequestValidator::validate(req);
    if(!valid.hasValue())
    {
        return Result::makeFailure(
            error::AppError {
                error::AppErrorType::InvalidRequest,
                error::StorageError::None,
                valid.error()
            });
    }

    auto getRes = domain.get(req.key);
    if(!getRes.hasValue())
    {
        return Result::makeFailure(
            error::AppError{
                error::AppErrorType::StorageFailure,
                getRes.error(),
                ""
            });            
    }

    return Result::makeSuccess(getRes.value());
}

} // namespace app::storage::services