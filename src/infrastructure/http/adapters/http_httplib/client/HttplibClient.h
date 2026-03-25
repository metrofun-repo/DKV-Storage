#pragma once

#include "infrastructure/http/client/HttpClient.h"
#include "infrastructure/http/client/HttpClientError.h"
#include "infrastructure/http/client/HttpClientResponsePayload.h"

namespace infra::http::adapters::httplib::client {

class HttplibClient : public http::client::HttpClient
{
public:
    PostResult post(
        std::string_view host,
        int port,
        std::string_view path,
        std::string_view body,
        std::size_t size,
        std::string_view contentType
    ) const override;
};

} // namespace infra::http::adapters::httplib::client