#pragma once

#include <string_view>

#include "core/types/Expected.h"
#include "infrastructure/http/server/HttpRequest.h"

namespace infra::http::validation {

class HttpRequestValidator
{
    using ValidationResult = core::types::Expected<void, std::string>;
public:
    static ValidationResult requireParam(const server::HttpRequest& req, std::string_view param);
    static ValidationResult requireBody(const server::HttpRequest& req);
};

} // namespace infra::http::validation