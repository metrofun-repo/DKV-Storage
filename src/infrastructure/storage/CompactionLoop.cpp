#include "CompactionLoop.h"

namespace infra::storage {

CompactionLoop::CompactionLoop(std::chrono::milliseconds period, storage::types::KeyValueStorage& storage)
    : kvStorage(storage)
    , worker(period, [this] { kvStorage.compact(); })
{}

void CompactionLoop::start()
{
    worker.start();
}
void CompactionLoop::stop()
{
    worker.stop();
}

} // namespace infra::storage