#pragma once

#include <string_view>

#include "infrastructure/http/server/HttpResponse.h"
#include "application/cluster/types/ReplicationApplyResult.h"

namespace app::cluster::builders {

class ReplicationResponseBuilder
{
    using HttpResponse = infra::http::server::HttpResponse;

public:
    static void from(HttpResponse& response, const app::cluster::types::ReplicationApplyResult& res);
};

} //namespace app::api::builders