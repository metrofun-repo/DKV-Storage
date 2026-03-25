#pragma once

#include <string>
#include <optional>
#include "common/utils/enum_utils.h"
#include "application/types/KeyValueTypes.h"
#include "domain/storage/model/VersionedValue.h"

namespace app::api::dto {

struct ExternalRequest
{
    enum class OperationType { Get, Set, Delete };
    OperationType operation;
    std::string key {};
    std::optional<app::types::Value> value = std::nullopt;
};

} // namespace app::api::dto

namespace common::enum_utils {

template<>
struct EnumValues<app::api::dto::ExternalRequest::OperationType>
{
    using Enum = app::api::dto::ExternalRequest::OperationType;
    static inline constexpr std::array<Enum, 3> values =
    {
        Enum::Get,
        Enum::Set,
        Enum::Delete
    };
};

} // namespace common::enum_utils