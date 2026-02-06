#pragma once

#include <string>
#include "third-party/httplib.h"

class HttpServer
{    
    std::string host;
    int port;
    httplib::Server srv;
public:
    HttpServer(const std::string& host, int port);

    inline std::string getHost() const { return host; }
    inline int getPort() const { return port; }

    template <typename Handler>
    void get(const std::string& pattern, Handler&& handler)
    {
        std::cout << getFormattedName() <<  " -> get call" << std:: endl;
        srv.Get(pattern, std::forward<Handler>(handler));
    }

    template <typename Handler>
    void post(const std::string& pattern, Handler&& handler)
    {
        std::cout << getFormattedName() << " -> post call" << std:: endl;
        srv.Post(pattern, std::forward<Handler>(handler));
    }

    template <typename Handler>
    void remove(const std::string& pattern, Handler&& handler)
    {
        std::cout << getFormattedName() << " -> remove call" << std:: endl;
        srv.Delete(pattern, std::forward<Handler>(handler));
    }

    std::string getFormattedName() const { return "DKVServer [" + host + ":" + std::to_string(port) + "]"; }

    void start();
    void stop();
};