#pragma once

#include <thread>
#include <atomic>
#include <chrono>
#include <functional>

namespace infra::concurrency {

class PeriodicTask
{
public:
    using Fn = std::function<void()>;
    explicit PeriodicTask(std::chrono::milliseconds period, Fn fn);
    ~PeriodicTask();

    void start();
    void stop();
    
private:
    std::chrono::milliseconds period;
    Fn fn;
    std::thread thread;
    std::atomic<bool> running = false;
};

} // namespace infra::concurrency