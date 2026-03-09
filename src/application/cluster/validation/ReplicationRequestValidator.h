#pragma once

#include "application/cluster/protocol/ReplicationRequest.h"

namespace app::cluster::validation {

class ReplicationRequestValidator
{
    using ValidationResult = core::types::Expected<void, std::string>;
    using ReplicationRequest = app::cluster::protocol::ReplicationRequest;
public:
    static ValidationResult validate(const ReplicationRequest& msg);
};

} // namespace app::cluster::validation