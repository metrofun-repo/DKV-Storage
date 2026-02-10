#include "ReplicationClient.h"

#include <nlohmann/json.hpp>
#include "third-party/httplib.h"

#include "Peer.h"
#include "api/internal/Routes.h"

#include "cluster/protocol/ReplicationMessage.h"
#include "cluster/protocol/JsonSerializer.h"

ReplicationClient::ReplicationClient(const std::vector<Peer>& peers)
    : peers(peers)
{}

void ReplicationClient::replicate(ReplicationMessage msg) const
{
    nlohmann::json json = toJson(std::move(msg));
    const std::string body = json.dump();

    for(auto& [host, port] : peers)
    {
        httplib::Client client(host, port);
        httplib::Result result = client.Post(ReplicationRoutes::REPLICATE, body, "application/json");
        if(!result)
        {
            std::cout << "\t[" << host << " : " << port <<"] replicate op: " << json["op"] << " HTTP Error : " << httplib::to_string(result.error()) << std::endl;
        }
        else
        {
            std::cout << "\t[" << host << " : " << port <<"] replicate op: " << json["op"] << " HTTP Status : " << result->status << " body: " << result->body << std::endl;
        }
    }

}