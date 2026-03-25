#pragma once

#include "domain/replication/error/ReplicationErrorCode.h"
#include "infrastructure/transport/error/TransportErrorCode.h"

namespace app::cluster::mapping {

domain::replication::error::ReplicationErrorCode fromTransport(infra::transport::error::TransportErrorCode code);

}