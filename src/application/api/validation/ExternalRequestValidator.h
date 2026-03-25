#pragma once

#include "core/types/BasicResult.h"
#include "application/api/requests/ExternalRequest.h"

namespace app::api::validation {

class ExternalRequestValidator
{
public:
    static core::types::BasicResult<void> validate(const dto::ExternalRequest& req);
};

} // namespace app::api::validation