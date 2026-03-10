#include "ClientResponse.h"

namespace app::api::dto {

// json response structure
// {
//   success   : true/false
//   status    : string
//   message   : string
//   [opt]data : json
// }
ClientResponse::Json ClientResponse::toJson() const
{
    common::json::json_t json {
        { "success", success },
        { "status" , status  },
        { "message", message },
    };
    if(!data.empty())
    {
        json["data"] = data;
    }
    return json;
}

ClientResponse::Result ClientResponse::fromJson(const Json& json)
{
    //TODO
    ClientResponse res{};
    // res.success = common::json::getBool(json, "success");
    // res.status  = common::json::getString(json, "status");
    // res.message = common::json::getString(json, "message");
    // res.data    = json.contains("data") ? json["data"] : common::json::json_t {};
    return Result::makeSuccess(res);
}

} // namespace app::api::dto