#pragma once

#include <string>

namespace domain::replication::error {

template <typename ErrorT>
struct NodeError
{
    std::string node;
    ErrorT error;
};

} // namespace domain::replication::error