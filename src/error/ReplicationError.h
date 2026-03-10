#pragma once

namespace error {

enum class ReplicationError
{
    None = 0,
    
    InvalidRequest,

    NodeUnreachable,
    NodeTimeout,
    NodeInvalidResponse,

    LocalApplyFailed,
    RemoteApplyFailed,

    QuorumNotReached,
    InternalError,

    Unknown
};

} // namespace error