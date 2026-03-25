#pragma once

#include <optional>
#include <functional>
#include <string_view>
#include <nlohmann/json.hpp>
#include "core/types/BasicResult.h"

namespace common::json {

using core::types::BasicResult;

using json_t = nlohmann::json;

inline core::types::BasicResult<json_t> parse(std::string_view input)
{
    try
    {
        return core::types::BasicResult<json_t>::makeSuccess(json_t::parse(input));
    }
    catch(const std::exception& e)
    {
        return core::types::BasicResult<json_t>::makeFailure(e.what());
    }
}

template <typename T>
inline bool typeMatch(const json_t& json, std::string_view key);
template <> inline bool typeMatch<     bool    >(const json_t& json, std::string_view key) { return json[key].is_boolean(); }
template <> inline bool typeMatch< std::string >(const json_t& json, std::string_view key) { return json[key].is_string(); }
template <> inline bool typeMatch<   int64_t   >(const json_t& json, std::string_view key) { return json[key].is_number_integer(); }
template <> inline bool typeMatch<   uint32_t  >(const json_t& json, std::string_view key) { return json[key].is_number_unsigned(); }
template <> inline bool typeMatch<   uint64_t  >(const json_t& json, std::string_view key) { return json[key].is_number_unsigned(); }
template <> inline bool typeMatch<    json_t   >(const json_t& json, std::string_view key) { return json[key].is_structured(); }

template <typename T> 
inline BasicResult<T> getValue(const json_t& json, std::string_view key)
{
    if(!json.contains(key))
    {
        return core::types::BasicResult<T>::makeFailure("JSON parse error : missing '" + std::string(key) +"'");
    }
    if(!typeMatch<T>(json, key))
    {
        return core::types::BasicResult<T>::makeFailure("JSON parse error : invalid type '" + std::string(key) +"'");
    }

    try
    {
        return core::types::BasicResult<T>::makeSuccess(json.at(key).get<T>());
    }
    catch(const std::exception& e)
    {
        return core::types::BasicResult<T>::makeFailure("JSON parse error : " + std::string(e.what()));
    }
}

template <typename T> 
inline BasicResult<std::optional<T>> getOptionalValue(const json_t& json, std::string_view key)
{
    if(!json.contains(key))
    {
        return core::types::BasicResult<std::optional<T>>::makeSuccess(std::nullopt);
    }
    if(!typeMatch<T>(json, key))
    {
        return core::types::BasicResult<std::optional<T>>::makeFailure("JSON parse error : invalid type '" + std::string(key) +"'");
    }
    try
    {
        return core::types::BasicResult<std::optional<T>>::makeSuccess(json.at(key).get<T>());
    }
    catch(const std::exception& e)
    {
        return core::types::BasicResult<std::optional<T>>::makeFailure("JSON parse error : " + std::string(e.what()));
    }
}

} // namespace common::json