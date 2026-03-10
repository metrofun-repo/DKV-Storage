#pragma once

#include "application/api/requests/ClientRequest.h"

namespace app::api::validation {

class ClientRequestValidator
{
    using ValidationResult = core::types::Expected<void, std::string>;
public:
    static ValidationResult validate(const app::api::dto::ClientRequest& msg);
};

} // namespace app::api::validation