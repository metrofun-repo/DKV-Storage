#include "ExternalRequestValidator.h"

namespace app::api::validation {

using ValidationResult = core::types::BasicResult<void>;
using OperationType = dto::ExternalRequest::OperationType;

ValidationResult ExternalRequestValidator::validate(const dto::ExternalRequest& req)
{
    if(req.key.empty())
    {
        return ValidationResult::makeFailure("'key' cannot be empty");
    }

    if(req.operation == OperationType::Set && !req.value.has_value())
    {
        return ValidationResult::makeFailure("'value' is required for set");
    }

    return ValidationResult::makeSuccess();
}

} // namespace app::api::validation