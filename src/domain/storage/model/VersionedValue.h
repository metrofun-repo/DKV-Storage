#pragma once

#include <variant>

namespace domain::storage::model {

struct TombstoneTag {};

template<typename T>
struct VersionedValue
{
    std::variant<T, TombstoneTag> value;
    int64_t timestamp;

    static VersionedValue tombstone(int64_t ts)
    {
        return VersionedValue { TombstoneTag{}, ts};
    }

    bool isTombstone() const
    {
        return std::holds_alternative<TombstoneTag>(value);
    }
};

} // namespace domain::storage::model