#pragma once

class IRequest;
class IResponse;
class KeyValueService;

class HttpMethodHandler
{
    KeyValueService& service;
public:
    HttpMethodHandler(KeyValueService& service);

    void handleSet(const IRequest& req, IResponse& res);
    void handleGet(const IRequest& req, IResponse& res);
    void handleRemove(const IRequest& req, IResponse& res);
};