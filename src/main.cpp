#include "app/DKVApp.h"

AppConfig parseArgs(int argc, char* argv[])
{
    AppConfig cfg;    

    for(int i = 0; i < argc; ++i)
    {
        std::string arg = argv[i];

        if(arg == "--host" && i + 1 < argc)
        {
            cfg.host = argv[++i];
        }
        else if(arg == "--port" && i + 1 < argc)
        {
            cfg.port = std::stoi(argv[++i]);
        }
        else if(arg == "--peer" && i + 1 < argc)
        {
            std::string peer = argv[++i];
            auto pos = peer.find(':');
            if(pos == std::string::npos)
            {
                throw std::runtime_error("Invalid peer format, expected host:port");
            }
            cfg.peers.emplace_back(peer.substr(0, pos), std::stoi(peer.substr(pos + 1)));
        }
        else if(arg == "dkv_server.exe")
        {
            continue;
        }
        else
        {
            std::cerr << "Unknown argumnet: " << arg << std::endl;
        }
    }
    return cfg;
}

int main(int argc, char* argv[])
{
    DKVApp app(parseArgs(argc, argv));

    app.run();

    return 0;
}