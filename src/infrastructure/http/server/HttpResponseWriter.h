#pragma once

#include "HttpResponse.h"
#include "common/utils/json_utils.h"
#include "infrastructure/serialization/SerializedMessage.h"

namespace infra::http::server {

class HttpResponseWriter
{
public:
    static void write(HttpResponse& response, int statusCode, const infra::serialization::SerializedMessage& data)
    {
        response.setStatus(statusCode);
        response.setContent(reinterpret_cast<const char*>(data.bytes.data()), data.bytes.size(), data.contentType);
    }
};

} // namespace infra::http::server