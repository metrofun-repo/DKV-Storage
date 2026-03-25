#pragma once
#include <string_view>
namespace infra::http::routing::routes {

    inline constexpr std::string_view EXTERNAL { "/kv" };
    inline constexpr std::string_view INTERNAL { "/cluster" };

} // namespace infra::http::server::routes