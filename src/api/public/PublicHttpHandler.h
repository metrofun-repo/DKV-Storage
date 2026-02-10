#pragma once

class IRequest;
class IResponse;
class KeyValueService;

class ReplicationService;

class PublicHttpHandler
{
    KeyValueService& service;
    ReplicationService& replicaService;
public:
    PublicHttpHandler(KeyValueService& service, ReplicationService& replica);

    void handleSet(const IRequest& req, IResponse& res);
    void handleGet(const IRequest& req, IResponse& res);
    void handleRemove(const IRequest& req, IResponse& res);
};