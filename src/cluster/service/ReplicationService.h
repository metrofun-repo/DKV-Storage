#pragma once

#include <string>

class KeyValueService;
class IReplicationClient;

class ReplicationService
{
    KeyValueService& kvService;
    IReplicationClient& replicaClient;
public:
    ReplicationService(KeyValueService& service, IReplicationClient& client);

    void replicateSet(const std::string& key, const std::string& value);
    void replicateRemove(const std::string& key);
};