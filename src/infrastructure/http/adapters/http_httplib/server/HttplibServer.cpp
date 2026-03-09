#include "HttplibServer.h"

#include "HttplibServerRequest.h"
#include "HttplibServerResponse.h"

namespace infra::http::adapters::httplib::server {

using libRequest  = ::httplib::Request;
using libResponse = ::httplib::Response;

HttplibServer::HttplibServer(NodeInfo info)
    : nodeInfo(std::move(info))
{
    srv.set_logger([](const auto& req, const auto& res) { std::cout << req.method << " " << req.path << " -> " << res.status << std::endl; });
}
HttplibServer::HttplibServer(std::string nodeId, std::string host, int port)
    : nodeInfo(std::move(nodeId), std::move(host), port)
{}

void HttplibServer::printServerInfo(std::string_view msg) const
{
    auto [nodeId, host, port] = nodeInfo;
    std::cout << nodeId << " [" << host << ":" << port << "]" << msg << std:: endl;
}

void HttplibServer::get(const std::string& path, HandlerFunc handler)
{
    printServerInfo(std::string(" -> ") + __func__ + " call");
    srv.Get(path, [handler = std::move(handler)](const libRequest& req, libResponse& res)
    {
        HttplibServerRequest request(req);
        HttplibServerResponse response(res);
        handler(request, response);
    });
}

void HttplibServer::set(const std::string& path, HandlerFunc handler)
{
    printServerInfo(path + std::string(" -> ") + __func__ + " call");
    srv.Post(path, [handler = std::move(handler)](const libRequest&  req, libResponse& res)
    {
        HttplibServerRequest request(req);
        HttplibServerResponse response(res);
        handler(request, response);
    });
}

void HttplibServer::remove(const std::string& path, HandlerFunc handler)
{
    printServerInfo(std::string(" -> ") + __func__ + " call");
    srv.Delete(path, [handler = std::move(handler)](const libRequest&  req, libResponse& res)
    {
        HttplibServerRequest request(req);
        HttplibServerResponse response(res);
        handler(request, response);
    });
}

void HttplibServer::start()
{
    printServerInfo(std::string("listening '0.0.0.0:") + std::to_string(nodeInfo.port) + "'");
    bool result = srv.listen("0.0.0.0", nodeInfo.port);
    if(!result)
    {
        printServerInfo("listen attempt failed");
    }
}

void HttplibServer::stop()
{
    srv.stop();
}

} // namespace infra::http::adapters::httplib::server