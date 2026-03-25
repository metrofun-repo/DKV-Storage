#pragma once

#include "JsonTraits.h"
#include "core/types/Error.h"
#include "common/utils/enum_utils.h"

#include "domain/replication/error/NodeError.h"


namespace infra::serialization::traits {

template <typename ErrorT>
struct JsonTraits<domain::replication::error::NodeError<ErrorT>>
{
    using Error     = ErrorT;
    using NodeError = domain::replication::error::NodeError<ErrorT>;
    using Json      = common::json::json_t;

    static Json toJson(const NodeError& obj)
    {
        return {
            { "node", obj.node },
            { "error", JsonTraits<Error>::toJson(obj.error) }
        };
    }
    static ParseResult<NodeError> fromJson(const Json& json)
    {
        NodeError obj;
        auto nodeStr = common::json::getValue<std::string>(json, "node");
        if(!nodeStr.hasValue())
        {
            return ParseResult<NodeError>::makeFailure(nodeStr.error());
        }
        obj.node = nodeStr.value();

        auto errorParse = common::json::getValue<Json>(json, "error");
        if(!errorParse.hasValue())
        {
            return ParseResult<NodeError>::makeFailure(errorParse.error());
        }
        obj.error = errorParse.value();

        return ParseResult<NodeError>::makeSuccess(obj);
    }
};

} // namespace infra::serialization::traits 