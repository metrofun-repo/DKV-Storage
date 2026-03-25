#include "HeartbeatLoop.h"

namespace app::cluster::heartbeat {

HeartbeatLoop::HeartbeatLoop(std::chrono::milliseconds period, services::HeartbeatService& service)
    : hbService(service)
    , worker(period, [this] { hbService.tick(); })
{}

void HeartbeatLoop::start()
{
    worker.start();
}
void HeartbeatLoop::stop()
{
    worker.stop();
}

}