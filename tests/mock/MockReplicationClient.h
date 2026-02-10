#pragma once

#include "interfaces/IReplicationClient.h"
#include "cluster/protocol/ReplicationMessage.h"

#include "cluster/protocol/JsonSerializer.h"

class MockReplicationClient : public IReplicationClient
{
public:
    mutable std::string body;
    void replicate(ReplicationMessage msg) const override
    {
        body.assign(toJson(std::move(msg)).dump());
    }
};