#pragma once

#include "infrastructure/concurrency/PeriodicTask.h"
#include "infrastructure/storage/types/KeyValueStorage.h"

namespace infra::storage {

class CompactionLoop
{
public:
    explicit CompactionLoop(std::chrono::milliseconds period, 
        storage::types::KeyValueStorage& storage);
    void start();
    void stop();

private:
    storage::types::KeyValueStorage& kvStorage;
    infra::concurrency::PeriodicTask worker;
};

} // namespace infra::storage