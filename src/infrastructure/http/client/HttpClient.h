#pragma once

#include <string>
#include <optional>
#include <string_view>
#include "core/types/Expected.h"

namespace infra::http::client {

struct HttpClientResponsePayload;
struct HttpClientError;

class HttpClient
{
protected:
    using PostResult = core::types::Expected<HttpClientResponsePayload, HttpClientError>;
public:
    virtual ~HttpClient() = default;    
    virtual PostResult post(
        std::string_view host,
        int port,
        std::string_view path,
        std::string_view body,
        std::string_view contentType
    ) const = 0;
};

} // namespace infra::http::client