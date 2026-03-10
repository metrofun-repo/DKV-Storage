#pragma once

#include <unordered_map>
#include <functional>

#include "application/api/requests/ClientRequest.h"
#include "application/api/responses/ClientResponse.h"

namespace app::api::handlers {

template <typename Op, typename Req, typename Resp>
class BaseOperationHandler
{
protected:
    using operation_t = Op;
    using request_t   = Req;
    using response_t  = Resp;

    using handler_fn = std::function<Resp(const Req& req)>;
    using result_t   = core::types::BasicResult<Resp>;
public:
    virtual ~BaseOperationHandler() =default;

    result_t handle(const request_t& req) const
    {
        auto it = handlers.find(req.operation);
        if(it == handlers.end())
        {
            return result_t::makeFailure("Unknown operation");
        }

        return result_t::makeSuccess(it->second(req));
    }
protected:
    BaseOperationHandler() = default;

    virtual void registerHandlers() = 0;

    std::unordered_map<operation_t, handler_fn> handlers;
};

} // namespace app::api::handlers