#pragma once

#include <cstddef>
#include "core/types/Expected.h"

namespace infra::transport::error { struct TransportError; }
namespace app::cluster::protocol { struct ReplicationRequest; }
namespace domain::cluster::model { struct NodeInfo; }

namespace infra::transport::senders {

class ReplicationSender
{
protected:
    using ReplicationRequest = app::cluster::protocol::ReplicationRequest;
    using NodeInfo           = domain::cluster::model::NodeInfo;
    using TransportError     = infra::transport::error::TransportError;
    using TransportSendResult = core::types::Expected<void, TransportError>;
public:
    virtual ~ReplicationSender() = default;    
    virtual core::types::Expected<void, TransportError> send(
        const ReplicationRequest& req,
        const NodeInfo& node) const = 0;
};

} // namespace infra::transport::senders