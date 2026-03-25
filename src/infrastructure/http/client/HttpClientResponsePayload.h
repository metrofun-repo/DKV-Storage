#pragma once

#include <string>
namespace infra::http::client {

struct HttpClientResponsePayload
{
    int status;
    std::string body;
};

} // namespace infra::http::client