#include "ReplicationService.h"

#include <chrono>
#include "storage/KeyValueService.h"

#include "cluster/protocol/ReplicationMessage.h"
#include "cluster/replication/ReplicationClient.h"

ReplicationService::ReplicationService(KeyValueService& service, IReplicationClient& client)
    : kvService(service)
    , replicaClient(client)
{
}

void ReplicationService::replicateSet(const std::string& key, const std::string& value)
{
    uint64_t timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    ReplicationMessage msg { OperationType::Set, key, value, timestamp };
    kvService.set(key, value, timestamp);
    replicaClient.replicate(std::move(msg));
}

void ReplicationService::replicateRemove(const std::string& key)
{
    ReplicationMessage msg { OperationType::Remove, key, std::nullopt, 0 };
    kvService.remove(key);
    replicaClient.replicate(std::move(msg));
}
