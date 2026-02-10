#pragma once

#include <string>

using timestamp_t = uint64_t;

struct ReplicationMessage;

class IReplicationClient
{
public:
    virtual void replicate(ReplicationMessage msg) const = 0;

    virtual ~IReplicationClient() = default;
};