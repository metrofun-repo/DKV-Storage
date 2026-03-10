#include "ClientRequestValidator.h"

namespace app::api::validation {

ClientRequestValidator::ValidationResult ClientRequestValidator::validate(const app::api::dto::ClientRequest& msg)
{
    using app::api::types::ClientOperationType;

    if(msg.key.empty())
    {
        return ValidationResult::makeFailure("'key' cannot be empty");
    }

    if(msg.operation == ClientOperationType::Set && !msg.value.has_value())
    {
        return ValidationResult::makeFailure("'value' is required for set");
    }

    if(msg.operation != ClientOperationType::Set && msg.operation != ClientOperationType::Delete)
    {
        return ValidationResult::makeFailure("Unknown operation");
    }

    return ValidationResult::makeSuccess();
}

} // namespace app::api::validation