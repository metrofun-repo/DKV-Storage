#pragma once

#include <string>

namespace core::types {

template <typename E>
struct Error
{
    E code;
    std::string message;

    Error(E c) : code(c) {}
    Error(E c = E(), std::string msg = {}) : code(c), message(std::move(msg)) {}
};

} // namespace common::types