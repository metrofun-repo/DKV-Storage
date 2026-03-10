#pragma once

#include <optional>
#include "TransportErrorCode.h"

namespace infra::transport::error {

struct TransportError
{
    TransportErrorCode code;
    std::optional<int> httpStatus;
};

} // namespace infra::transport::senders