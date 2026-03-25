#pragma once

#include <vector>
#include <string>

#include "domain/replication/error/NodeError.h"

namespace domain::replication {

template <typename ErrorT>
struct FanoutResult
{
    std::vector<std::string> acknowledged;
    std::vector<error::NodeError<ErrorT>> failed;
};

} // namespace domain::replication