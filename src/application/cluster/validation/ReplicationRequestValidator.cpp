#include "ReplicationRequestValidator.h"

namespace app::cluster::validation {

ReplicationRequestValidator::ValidationResult ReplicationRequestValidator::validate(const ReplicationRequest& msg)
{
    if(msg.key.empty())
    {
        return ValidationResult::makeFailure("'key' cannot be empty");
    }

    if(msg.operation == ReplicationRequest::Operation::Set && !msg.value.has_value())
    {
        return ValidationResult::makeFailure("'value' is required for set operation");
    }

    if(msg.operation != ReplicationRequest::Operation::Set && msg.operation != ReplicationRequest::Operation::Delete )
    {
        return ValidationResult::makeFailure("Unknown operation");
    }

    return ValidationResult::makeSuccess();
}

} // namespace app::cluster::validation