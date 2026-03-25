#pragma once

#include "JsonTraits.h"
#include "application/api/requests/ExternalRequest.h"

namespace infra::serialization::traits {

template <>
struct JsonTraits<app::api::dto::ExternalRequest>
{
    using ExternalRequest = app::api::dto::ExternalRequest;
    using Operation     = typename app::api::dto::ExternalRequest::OperationType;
    using Json          = common::json::json_t;

    static Json toJson(const ExternalRequest& obj)
    {
        Json json {
            { "op", static_cast<uint32_t>(obj.operation)},
            { "key", obj.key }
        };
        if(obj.value.has_value())
        {
            json["value"] = obj.value;
        }
        return json;
    }

    static ParseResult<ExternalRequest> fromJson(const Json& json)
    {
        ExternalRequest obj;

        auto op = common::json::getValue<uint32_t>(json, "op");
        if(!op.hasValue())
        {
            return ParseResult<ExternalRequest>::makeFailure(op.error());
        }
        auto opCast = common::enum_utils::safeEnumCast<Operation>(op.value());
        if(!opCast.hasValue())
        {
            return ParseResult<ExternalRequest>::makeFailure(opCast.error());
        }
        obj.operation = opCast.value();

        auto expKeyStr = common::json::getValue<std::string>(json, "key");
        if(!expKeyStr.hasValue())
        {
            return ParseResult<ExternalRequest>::makeFailure(expKeyStr.error());
        }
        obj.key = expKeyStr.value();

        auto expOptStr = common::json::getOptionalValue<std::string>(json, "value");
        if(!expOptStr.hasValue())
        {
            return ParseResult<ExternalRequest>::makeFailure(expOptStr.error());
        }
        obj.value = expOptStr.value();
    
        return ParseResult<ExternalRequest>::makeSuccess(obj);
    }
};

} // namespace infra::serialization::traits