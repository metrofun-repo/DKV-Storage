#pragma once

#include <optional>
#include <functional>
#include <string_view>
#include <nlohmann/json.hpp>
#include "core/types/BasicResult.h"

namespace common::json {

using core::types::BasicResult;

using json_t = nlohmann::json;
using JsonCheckPredicate = std::function<bool(const json_t&, std::string_view)>;

inline bool hasBool(const json_t& json, std::string_view key)
{
    return json.contains(key) && json[key].is_boolean();
}

inline bool hasString(const json_t& json, std::string_view key)
{
    return json.contains(key) && json[key].is_string();
}

inline bool hasUnsigned(const json_t& json, std::string_view key)
{
    return json.contains(key) && json[key].is_number_unsigned();
}

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
inline core::types::BasicResult<T> getValue(const json_t& json, std::string_view key, JsonCheckPredicate predicate)
{
    if(!predicate(json, key))
    {
        return core::types::BasicResult<T>::makeFailure("JSON parse error : missing '" + std::string(key) +"'");
    }
    return core::types::BasicResult<T>::makeSuccess(json[key].get<T>());
}

template <typename T> 
inline core::types::BasicResult<std::optional<T>> getOptionalValue(const json_t& json, std::string_view key, JsonCheckPredicate predicate)
{
    if(!json.contains(key))
    {
        return core::types::BasicResult<std::optional<T>>::makeSuccess(std::nullopt);
    }
    if(!predicate(json, key))
    {
        return core::types::BasicResult<std::optional<T>>::makeFailure("JSON parse error : invalid '" + std::string(key) +"'");
    }
    return core::types::BasicResult<std::optional<T>>::makeSuccess(json[key].get<T>());
}

inline core::types::BasicResult<bool> getBool(const json_t& json, std::string_view key)
{
    return getValue<bool>(json, key, [] (const json_t& j, std::string_view k) { return hasBool(j, k); });
}

inline core::types::BasicResult<std::string> getString(const json_t& json, std::string_view key)
{
    return getValue<std::string>(json, key, [] (const json_t& j, std::string_view k) { return hasString(j, k); });
}

inline core::types::BasicResult<uint64_t> getUnsigned(const json_t& json, std::string_view key)
{
    return getValue<uint64_t>(json, key, [] (const json_t& j, std::string_view k) { return hasUnsigned(j, k); });
}

inline core::types::BasicResult<std::optional<std::string>> getOptionalString(const json_t& json, std::string_view key)
{
    return getOptionalValue<std::string>(json, key, [](const json_t& j, std::string_view k) { return j[k].is_string(); });
}

} // namespace common::json