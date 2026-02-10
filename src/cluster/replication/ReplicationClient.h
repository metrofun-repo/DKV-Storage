#pragma once

#include <string>
#include <vector>

#include "interfaces/IReplicationClient.h"

struct Peer;
struct ReplicationMessage;

class ReplicationClient : public IReplicationClient
{
    const std::vector<Peer>& peers;
public:
    ReplicationClient(const std::vector<Peer>& peers);

    void replicate(ReplicationMessage msg) const override;
};
