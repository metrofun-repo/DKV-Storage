#pragma once

#include <string>

namespace infra::http::client {

enum class HttpClientErrorCode
{
    Read,
    Write,
    Timeout,
    Connection,
    Unknown
};

struct HttpClientError
{
    HttpClientErrorCode code;
    std::string message;
};

} // namespace infra::http::client