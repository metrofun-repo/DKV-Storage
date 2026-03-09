#pragma once

#include "error/AppError.h"

#include "application/types/KeyValueTypes.h"
#include "application/api/requests/ClientRequest.h"
#include "domain/storage/services/KeyValueService.h"

namespace app::storage::services {

class QueryService
{
    using Key            = app::types::Key;
    using Value          = app::types::Value;
    using ClientRequest  = app::api::dto::ClientRequest;

    using VersionedValue = domain::storage::model::VersionedValue<Value>;
    using StorageService = domain::storage::services::KeyValueService<Key, Value>;
    
    using Result = core::types::Expected<VersionedValue, error::AppError>;
    
public:
    explicit QueryService(StorageService& kvService);
    Result get(const ClientRequest& req) const;

private:
    StorageService& domain;
};

} // namespace app::storage::services