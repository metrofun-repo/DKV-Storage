#pragma once

#include <string>
#include <optional>

#include "MessageType.h"

struct ReplicationMessage
{
    OperationType operation;
    std::string key;
    std::optional<std::string> value;
    uint64_t timestamp;

    ReplicationMessage() = default;

    ReplicationMessage(const ReplicationMessage& other) = delete;
    ReplicationMessage& operator=(ReplicationMessage& other) = delete;
    
    ReplicationMessage(ReplicationMessage&& other) noexcept = default;
    ReplicationMessage& operator=(ReplicationMessage&& other) noexcept = default;
};