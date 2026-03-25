#pragma once 
#include "ExternalResponseBuilder.h"

#include <string_view>
#include "infrastructure/serialization/traits/JsonTraitsVersionedValue.h"

namespace app::api::builders {

using AppErrorCode     = error::AppErrorCode;
using ValueTraits      = infra::serialization::traits::JsonTraits<app::types::VersionedValue>;
using ExternalResponse = dto::ExternalResponse;

ExternalResponse ExternalResponseBuilder::from(const QueryResult& result)
{
    if(!result.hasValue())
    {
        return mapAppError(result.error());
    }
    return { true, "OK", "Operation completed successfully", ValueTraits::toJson(result.value()) };
}

ExternalResponse ExternalResponseBuilder::from(const ReplicationResult& result)
{
    if(!result.hasValue())
    {
        return mapAppError(result.error());
    }
    return { true, "OK", "Operation completed successfully", {} };
}

ExternalResponse ExternalResponseBuilder::mapAppError(const error::AppError& error)
{
    switch (error.code)
    {
        case error::AppErrorCode::KeyNotFound    :
        case error::AppErrorCode::StorageFailure : return { false, "LOCAL_STORAGE_ERROR", error.message, {} };
        case error::AppErrorCode::InvalidRequest :
        default                                  : return { false, "INVALID_REQUEST", error.message, {} };
    }
}

} // namespace app::api::builder


