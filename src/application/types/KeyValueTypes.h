#pragma once

#include <string>
#include "domain/storage/model/VersionedValue.h"

namespace app::types {
    using Key   = std::string;
    using Value = std::string;
    using VersionedValue = domain::storage::model::VersionedValue<Value>;
}