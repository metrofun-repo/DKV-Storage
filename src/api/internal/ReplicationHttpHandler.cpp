#include "ReplicationHttpHandler.h"

#include <chrono>
#include <nlohmann/json.hpp>

#include "interfaces/IRequest.h"
#include "interfaces/IResponse.h"

#include "http/HttpServer.h"

#include "storage/KeyValueService.h"

#include "cluster/protocol/ReplicationMessage.h"
#include "cluster/protocol/JsonSerializer.h"

ReplicationHttpHandler::ReplicationHttpHandler(KeyValueService& service)
    : service(service)
{}

void ReplicationHttpHandler::handleReplicate(const IRequest& req, IResponse& res)
{
    if(req.getBody().empty())
    {
        res.setStatus(httplib::StatusCode::BadRequest_400);
        res.setContent("Request 'body' is empty", "text/plain");
        return;
    }

    auto json = nlohmann::json::parse(req.getBody());
    ReplicationMessage msg { fromJson(json) };

    httplib::StatusCode code { httplib::StatusCode::BadRequest_400 };
    std::string content { std::string("Unknown replication operation: ") + std::to_string(static_cast<int>(msg.operation))};
    switch(msg.operation)
    {
        case OperationType::Set :
        {
            if(!msg.value.has_value())
            {
                content = "'value' cannot be empty";
            }
            else
            {
                service.set(msg.key, msg.value.value(), msg.timestamp);
                code = httplib::StatusCode::OK_200;
                content = "Value succesfully saved";
            }
        } break;
        case OperationType::Remove :
        {
            service.remove(msg.key);
            code = httplib::StatusCode::OK_200;
            content = "Value succesfully removed";  
        } break;
        default : break;
    }
    
    res.setStatus(code);
    res.setContent(content, "text/plain");
}