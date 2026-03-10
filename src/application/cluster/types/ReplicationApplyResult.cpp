#include "ReplicationApplyResult.h"

#include <unordered_map>

namespace app::cluster::types {

ReplicationApplyResult::ReplicationApplyResult(bool ok, error::ReplicationError code)
    : applied(ok)
    , error(code)
{}

ReplicationApplyResult::ErrorParseResult  ReplicationApplyResult::parseError(uint64_t error)
{
    static std::unordered_map<int, error::ReplicationError> map = 
    {
        { static_cast<uint64_t>(error::ReplicationError::None)                , error::ReplicationError::None                },
        { static_cast<uint64_t>(error::ReplicationError::InvalidRequest)      , error::ReplicationError::InvalidRequest      },
        { static_cast<uint64_t>(error::ReplicationError::NodeUnreachable)     , error::ReplicationError::NodeUnreachable     },
        { static_cast<uint64_t>(error::ReplicationError::NodeTimeout)         , error::ReplicationError::NodeTimeout         },
        { static_cast<uint64_t>(error::ReplicationError::NodeInvalidResponse) , error::ReplicationError::NodeInvalidResponse },
        { static_cast<uint64_t>(error::ReplicationError::LocalApplyFailed)    , error::ReplicationError::LocalApplyFailed    },
        { static_cast<uint64_t>(error::ReplicationError::RemoteApplyFailed)   , error::ReplicationError::RemoteApplyFailed   },
        { static_cast<uint64_t>(error::ReplicationError::QuorumNotReached)    , error::ReplicationError::QuorumNotReached    },
        { static_cast<uint64_t>(error::ReplicationError::InternalError)       , error::ReplicationError::InternalError       },
        { static_cast<uint64_t>(error::ReplicationError::Unknown)             , error::ReplicationError::Unknown             }
    };
    auto it = map.find(error);
    if(it == map.end())
    {
        return ErrorParseResult::makeFailure("Failed to parse replication error " + std::to_string(error));
    }
    return ErrorParseResult::makeSuccess(it->second);
}

ReplicationApplyResult::Json ReplicationApplyResult::toJson() const
{
    return {
        { "applied", applied },
        { "error" , static_cast<uint64_t>(error) },
    };
}

ReplicationApplyResult::JsonParseResult ReplicationApplyResult::fromJson(const Json& json)
{
    ReplicationApplyResult req;
    auto expApplied = common::json::getBool(json, "applied");
    if(!expApplied.hasValue())
    {
        return JsonParseResult::makeFailure(expApplied.error());
    }

    if(!expApplied.value())
    {
        auto expError = common::json::getUnsigned(json, "error_code");
        if(!expError.hasValue())
        {
            return JsonParseResult::makeFailure(expError.error());
        }
        auto errorParse = parseError(expError.value());
        if(!errorParse.hasValue())
        {
            return JsonParseResult::makeFailure(errorParse.error());
        }
    }
    return JsonParseResult::makeSuccess(req);
}

} // namespace app::cluster::types