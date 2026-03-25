#pragma once

#include "infrastructure/concurrency/PeriodicTask.h"
#include "application/cluster/services/HeartbeatService.h"

namespace app::cluster::heartbeat {

class HeartbeatLoop
{
public:
    explicit HeartbeatLoop(std::chrono::milliseconds period, 
        services::HeartbeatService& service);
    void start();
    void stop();

private:
    services::HeartbeatService& hbService;
    infra::concurrency::PeriodicTask worker;
};

}