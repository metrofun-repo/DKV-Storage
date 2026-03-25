#pragma once

#include "common/utils/json_utils.h"

namespace infra::serialization::traits {

template <typename T>
using ParseResult = core::types::BasicResult<T>;

template <typename T>
struct JsonTraits
{
    using Json = common::json::json_t;

    static Json toJson(const T& obj);
    static ParseResult<T> fromJson(const Json& json);
};

} // namespace infra::serialization::traits