#pragma once

#include "common/utils/json_utils.h"

namespace domain::storage::model {

template<typename T>
struct VersionedValue
{
    T value;
    uint64_t timestamp;
    
    common::json::json_t toJson() const
    {
        return {
            { "value", value },
            { "timestamp", timestamp }
        };
    }
};

} // namespace domain::storage::model