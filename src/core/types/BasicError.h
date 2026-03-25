#pragma once

#include "Error.h"

namespace core::types {

template<>
struct Error<void>
{
    std::string message;

    Error() = default;
    Error(std::string s) : message(std::move(s)) {}
    Error(const char* str) : message(str) {}

    operator const std::string& () const { return message; }
    operator const char * () { return message.c_str(); }
};

using BasicError = Error<void>;

} // namespace core::types