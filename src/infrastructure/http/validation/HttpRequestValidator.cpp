#include "HttpRequestValidator.h"

namespace infra::http::validation {

HttpRequestValidator::ValidationResult HttpRequestValidator::requireParam(const infra::http::server::HttpRequest& req, std::string_view param)
{
    if(!req.hasParam(param))
    {
        return ValidationResult::makeFailure("Missing param '" + std::string(param) + "\'");
    }
    return ValidationResult::makeSuccess();
}

HttpRequestValidator::ValidationResult HttpRequestValidator::requireBody(const infra::http::server::HttpRequest& req)
{
    if(req.getBody().empty())
    {
        return ValidationResult::makeFailure("Request body cannot be empty");
    }
    return ValidationResult::makeSuccess();
}

} // namespace infra::http::server::validation