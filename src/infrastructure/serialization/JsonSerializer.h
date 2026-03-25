#pragma once

#include "infrastructure/serialization/traits/JsonTraits.h"
#include "SerializedMessage.h"

namespace infra::serialization {

class JsonSerializer 
{
    template <typename T>
    using ParseResult = core::types::BasicResult<T>;

    template <typename T>
    using JsonTraits = traits::JsonTraits<T>;

    using Json = common::json::json_t;

public:
    template <typename T>
    static SerializedMessage serialize(const T& obj)
    {
        std::string payload = JsonTraits<T>::toJson(obj).dump();
        return  { 
            std::vector<uint8_t>(payload.begin(), payload.end()),
            "application/json"
        };
    }
    template <typename T>
    static ParseResult<T> deserialize(std::string_view sv)
    {
        auto strParse = common::json::parse(sv);
        if(!strParse.hasValue())
        {
            return ParseResult<T>::makeFailure(strParse.error());
        }
        auto jsonParse = JsonTraits<T>::fromJson(strParse.value());
        if(!jsonParse.hasValue())
        {
            return ParseResult<T>::makeFailure(jsonParse.error());
        }
        return ParseResult<T>::makeSuccess(jsonParse.value());
    }
};

} // namespace infra::serialization