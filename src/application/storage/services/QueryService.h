#pragma once

#include "application/types/StorageTypes.h"
#include "application/api/requests/ExternalRequest.h"
#include "application/api/responses/ExternalResponse.h"

namespace app::storage::services {

class QueryService
{   
public:
    explicit QueryService(app::types::StorageService& service);
    api::dto::ExternalResponse get(const api::dto::ExternalRequest& req) const;

private:
    app::types::StorageService& storage;
};

} // namespace app::storage::services