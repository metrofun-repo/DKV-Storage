#pragma once

#include <string>
// #include "core/types/Expected.h"
// #include "HttpClientError.h"

namespace infra::http::client {

struct HttpClientResponsePayload
{
    int status;
    std::string body;
};

// using HttpClientResponse = core::types::Expected<HttpClientResponsePayload, HttpClientError>;

} // namespace infra::http::client