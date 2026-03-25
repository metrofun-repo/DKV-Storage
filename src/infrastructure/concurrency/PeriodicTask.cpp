#include "PeriodicTask.h"

#include <cstdlib>

namespace infra::concurrency {

PeriodicTask::PeriodicTask(std::chrono::milliseconds period, Fn fn) : period(period), fn(fn)
{}

PeriodicTask::~PeriodicTask()
{
    stop();
}

void PeriodicTask::start()
{
    if(running) return;

    running.store(true);
    thread = std::thread([this](){
        while(running.load())
        {
            auto start = std::chrono::steady_clock::now();
            try
            {
                fn();
            }
            catch(const std::exception& e)
            {
                //TODO ADD LOGGING
            }

            auto jitter = std::chrono::milliseconds(std::rand() % 50);

            std::this_thread::sleep_until(start + period + jitter);
        }
    });
}

void PeriodicTask::stop()
{
    running.store(false);
    if(thread.joinable())
        thread.join();
}


} // namespace infra::concurrency