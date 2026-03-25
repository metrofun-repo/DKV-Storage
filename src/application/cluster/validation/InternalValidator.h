#pragma once

#include "core/types/BasicResult.h"
#include "application/cluster/protocol/InternalRequest.h"
#include "application/cluster/protocol/InternalResponse.h"

namespace app::cluster::validation {

class InternalValidator
{
    using ValidationResult = core::types::BasicResult<void>;
public:

    template <typename T, protocol::InternalResponse::Type Type>
    static ValidationResult validate(const protocol::InternalResponse& req)
    {
        if(req.type != Type)
        {
            return ValidationResult::makeFailure("Invalid internal response type");
        }
        
        if(std::holds_alternative<T>(req.payload))
        {
            return ValidationResult::makeFailure("Invalid internal response payload");
        }
        return ValidationResult::makeSuccess();
    }

    template <typename T, protocol::InternalRequest::Type Type>
    static ValidationResult validate(const protocol::InternalRequest& req)
    {
        if(req.type != Type)
        {
            return ValidationResult::makeFailure("Invalid internal request type");
        }
        
        if(std::holds_alternative<T>(req.payload))
        {
            return ValidationResult::makeFailure("Invalid internal request payload");
        }
        return ValidationResult::makeSuccess();
    }
};

} // namespace app::cluster::validation