#pragma once

#include <string_view>

#include "core/types/Expected.h"
#include "infrastructure/http/server/HttpRequest.h"

namespace infra::http::validation {

class HttpRequestValidator
{
    using ValidationResult = core::types::Expected<void, std::string>;
    using HttpRequest      = infra::http::server::HttpRequest;
public:
    static ValidationResult requireParam(const HttpRequest& req, std::string_view param);
    static ValidationResult requireBody(const HttpRequest& req);
};

} // namespace infra::http::validation