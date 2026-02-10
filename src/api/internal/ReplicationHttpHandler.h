#pragma once
class IRequest;
class IResponse;
class KeyValueService;

class ReplicationHttpHandler
{
    KeyValueService& service;
public:
    ReplicationHttpHandler(KeyValueService& service);

    void handleReplicate(const IRequest& req, IResponse& res);
};