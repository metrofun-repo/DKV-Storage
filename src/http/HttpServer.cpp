#include "HttpServer.h"

#include "http/adapters/HttplibRequestAdapter.h"
#include "http/adapters/HttplibResponseAdapter.h"

HttpServer::HttpServer(const std::string& host, int port)
    : host(host)
    , port(port)
{}

void HttpServer::get(const std::string& path, Handler handler)
{
    std::cout << "[" << host << ":" << port << "]" <<  " -> get call" << std:: endl;
    srv.Get(path, [handler = std::move(handler)](const httplib::Request&  req, httplib::Response& res)
    {
        HttplibRequestAdapter rq(req);
        HttplibResponseAdapter rs(res);
        handler(rq, rs);
    });
}

void HttpServer::set(const std::string& path, Handler handler)
{
    std::cout << "[" << host << ":" << port << "]" <<  " -> get call" << std:: endl;
    srv.Post(path, [handler = std::move(handler)](const httplib::Request&  req, httplib::Response& res)
    {
        HttplibRequestAdapter rq(req);
        HttplibResponseAdapter rs(res);
        handler(rq, rs);
    });
}

void HttpServer::remove(const std::string& path, Handler handler)
{
    std::cout << "[" << host << ":" << port << "]" <<  " -> get call" << std:: endl;
    srv.Delete(path, [handler = std::move(handler)](const httplib::Request&  req, httplib::Response& res)
    {
        HttplibRequestAdapter rq(req);
        HttplibResponseAdapter rs(res);
        handler(rq, rs);
    });
}

void HttpServer::start()
{
    std::cout << "[" << host << ":" << port <<"] listening '0.0.0.0: " << port << "'" << std::endl;
    bool result = srv.listen("0.0.0.0", port);
    if(!result)
    {
        std::cout << "[" << host << ":" << port <<"] listen attempt failed" << std::endl;
    }
}

void HttpServer::stop()
{
    srv.stop();
}