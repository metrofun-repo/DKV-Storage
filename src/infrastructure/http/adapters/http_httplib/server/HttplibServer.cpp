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

void HttplibServer::get(std::string_view path, HandlerFunc handler)
{
    printServerInfo(std::string(" -> ") + __func__ + " call");
    srv.Get(std::string(path), [handler = std::move(handler)](const libRequest& req, libResponse& res)
    {
        HttplibServerRequest request(req);
        HttplibServerResponse response(res);
        handler(request, response);
    });
}

void HttplibServer::set(std::string_view path, HandlerFunc handler)
{
    printServerInfo(std::string(path) + " -> " + __func__ + " call");
    srv.Post(std::string(path), [handler = std::move(handler)](const libRequest&  req, libResponse& res)
    {
        HttplibServerRequest request(req);
        HttplibServerResponse response(res);
        handler(request, response);
    });
}

void HttplibServer::remove(std::string_view path, HandlerFunc handler)
{
    printServerInfo(std::string(" -> ") + __func__ + " call");
    srv.Delete(std::string(path), [handler = std::move(handler)](const libRequest&  req, libResponse& res)
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