#pragma once 


#include "ApiResponseBuilder.h"

#include <string_view>

#include "common/utils/json_utils.h"

namespace {
    struct ErrorMapping
    {
        std::string_view status;
        std::string_view message;
    };

    static constexpr ErrorMapping replicationErrorTable[] =
    {
        /* None */               { "OK", "Success" },
        /* InvalidRequest */     { "INVALID_REQUEST", "Replication request is invalid"},
        /* NodeUnreachable */    { "REPLICATION_NODE_ERROR", "Node unreachable" },
        /* NodeTimeout */        { "REPLICATION_NODE_ERROR", "Node timeout" },
        /* NodeInvalidResponse */{ "REPLICATION_NODE_ERROR", "Invalid response from node" },
        /* LocalApplyFailed */   { "LOCAL_STORAGE_ERROR", "Local node failed to apply operation"},
        /* RemoteApplyFailed */  { "REPLICATION_REMOTE_APPLY_FAILED", "Remote node failed to apply operation"},
        /* QuorumNotReached */   { "REPLICATION_QUORUM_FAILED", "Quorum not reached" },
        /* InternalError */      { "REPLICATION_INTERNAL_ERROR", "Failed to prepare replication request" },
        /* Unknown */            { "INTERNAL_ERROR", "Unknown replication error" }
    };
    static constexpr ErrorMapping storageErrorTable[] =
    {
        /* None */           { "OK", "Success" },
        /* KeyNotFound */    { "LOCAL_STORAGE_ERROR", "Key not found" },
        /* StaleWrite */     { "LOCAL_STORAGE_ERROR", "Stale write detected" },
        /* InternalError */  { "LOCAL_STORAGE_ERROR", "Unknown storage error" },
    };

    static constexpr ErrorMapping mapError(error::ReplicationError err)
    {
        return replicationErrorTable[static_cast<std::size_t>(err)];
    }

    static constexpr ErrorMapping mapError(error::StorageError err)
    {
        return storageErrorTable[static_cast<std::size_t>(err)];
    }


    // ErrorMapping mapError(ReplicationError err)
    // {
    //     switch(err)
    //     {
    //         case ReplicationError::InvalidRequest      : return { "INVALID_REQUEST", "Replication request is invalid"};
    //         case ReplicationError::LocalApplyFailed    : return { "LOCAL_STORAGE_ERROR", "Local node failed to apply operation"};
    //         case ReplicationError::RemoteApplyFailed   : return { "REPLICATION_REMOTE_APPLY_FAILED", "Remote node failed to apply operation"};
    //         case ReplicationError::QuorumNotReached    : return { "REPLICATION_QUORUM_FAILED", "Quorum not reached" };
    //         case ReplicationError::NodeUnreachable     :  
    //         case ReplicationError::NodeTimeout         :  
    //         case ReplicationError::NodeInvalidResponse : return { "REPLICATION_NODE_ERROR", "One or more nodes failed" };
    //         case ReplicationError::InternalError       : return { "REPLICATION_INTERNAL_ERROR", "Failed to prepare replication request" };
    //         default                                    : return { "INTERNAL_ERROR", "Unknown replication error" };
    //     }
    // }

    // ErrorMapping mapError(StorageError err)
    // {
    //     switch(err)
    //     {
    //         case StorageError::KeyNotFound   : return { "LOCAL_STORAGE_ERROR", "Key not found" };
    //         case StorageError::StaleWrite    : return { "LOCAL_STORAGE_ERROR", "Stale write detected" }; 
    //         case StorageError::InternalError : return { "LOCAL_STORAGE_ERROR", "Internal storage failure" };
    //         default                          : return { "LOCAL_STORAGE_ERROR", "Unknown storage error" };
    //     }
    // }
}

namespace app::api::builders {

using AppErrorType = error::AppErrorType;

ApiResponseBuilder::ClientResponse ApiResponseBuilder::from(const QueryResult& result)
{
    if(!result.hasValue())
    {
        auto& error = result.error();
        switch (error.appError)
        {
            case AppErrorType::InvalidRequest : return { false, "INVALID_REQUEST", error.details, {} };
            case AppErrorType::StorageFailure : 
            {
                auto m = mapError(error.storageError);
                return { false, std::string(m.status), std::string(m.message), {} };
            }
            default : return { false, "INVALID_REQUEST", error.details, {} };
        }
    }
    return { true, "OK", "Operation completed successfully", result.value().toJson() };
}

ApiResponseBuilder::ClientResponse ApiResponseBuilder::from(const app::cluster::types::ReplicationResult& result)
{
    if(result.isLocalFailure())
    {
        auto m = mapError(result.localApply.error());
        return { false, std::string(m.status), std::string(m.message), {} };
    }

    if(result.isReplicationFailure())
    {
        auto m = mapError(result.replicaApply.error());
        return { false, std::string(m.status), std::string(m.message), result.fanout.toJson() };
    }
    return { true, "OK", "Operation completed successfully", {} };
}

ApiResponseBuilder::ClientResponse ApiResponseBuilder::from(const app::cluster::types::ReplicationApplyResult& result)
{
    if(!result.applied)
    {
        auto m = mapError(result.error);
        return { false, std::string(m.status), std::string(m.message), {} };
    }
    return { true, "OK", "Operation completed successfully", {} };
}

} // namespace app::api::builder


