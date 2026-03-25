#pragma once

#include "JsonTraits.h"
#include "application/api/responses/ExternalResponse.h"

namespace infra::serialization::traits {

template <>
struct JsonTraits<app::api::dto::ExternalResponse>
{
    using ExternalResponse = app::api::dto::ExternalResponse;
    using Json           = common::json::json_t;

    static Json toJson(const ExternalResponse& obj)
    {
        Json json {
            { "success", obj.success },
            { "status" , obj.status  },
            { "message", obj.message },
        };
        if(!obj.data.empty())
        {
            json["data"] = obj.data;
        }
        return json;
    }

    static ParseResult<ExternalResponse> fromJson(const Json& json)
    {
        ExternalResponse obj;
        auto success = common::json::getValue<bool>(json, "success");
        if(!success.hasValue())
        {
            return ParseResult<ExternalResponse>::makeFailure(success.error());
        }
        obj.success = success.value();

        auto status = common::json::getValue<std::string>(json, "status");
        if(!status.hasValue())
        {
            return ParseResult<ExternalResponse>::makeFailure(status.error());
        }
        obj.status = status.value();

        auto message = common::json::getValue<std::string>(json, "message");
        if(!message.hasValue())
        {
            return ParseResult<ExternalResponse>::makeFailure(message.error());
        }
        obj.message = message.value();

        auto data = common::json::getValue<common::json::json_t>(json, "data");
        if(data.hasValue())
        {
            obj.data = data.value();
        }
        return ParseResult<ExternalResponse>::makeSuccess(obj);
    }
};

} // namespace infra::serialization::traits