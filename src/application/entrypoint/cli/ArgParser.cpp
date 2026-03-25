#include "ArgParser.h"
#include <iostream>

namespace app::entrypoint::cli {

ArgParser::ArgParser(int argc, char** argv) : argc(argc), argv(argv)
{}

ArgParser::Result<AppConfig> ArgParser::parse()
{
    AppConfig cfg;
    for(int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if(arg == "--host")
        {
            auto res = readString(arg, i);
            if(!res.hasValue())
            {
                return Result<AppConfig>::makeFailure(res.error().message);
            }
            cfg.nodeInfo.host = res.value();
        }
        else if(arg == "--node")
        {
            auto res = readString(arg, i);
            if(!res.hasValue())
            {
                return Result<AppConfig>::makeFailure(res.error().message);
            }
            cfg.nodeInfo.nodeId = res.value();
        }
        else if(arg == "--port")
        {
            auto res = readInteger(arg, i);
            if(!res.hasValue())
            {
                return Result<AppConfig>::makeFailure(res.error().message);
            }
            cfg.nodeInfo.port = res.value();
        }
        else if(arg == "--peer")
        {
            auto res = parseNodes(cfg.nodes, i);
            if(!res.hasValue())
            {
                return Result<AppConfig>::makeFailure(res.error());
            }
        }
        else
        {
            return Result<AppConfig>::makeFailure("Unknown argumnet: " + arg);
        }
    }
    return Result<AppConfig>::makeSuccess(std::move(cfg));
}

ArgParser::Result<void> ArgParser::parseNodes(std::vector<domain::cluster::model::NodeInfo>& nodes, int& index)
{

    if(index + 1 >= argc)
    {
        return Result<void>::makeFailure("Missing value for argument: 'node'");
    }

    std::string nodeData = argv[++index];

    auto nodePos = findCharPos(nodeData, '@');
    if(!nodePos.hasValue())
    {
        return Result<void>::makeFailure(nodePos.error());
    }

    auto hostPos = findCharPos(nodeData, ':');
    if(!hostPos.hasValue())
    {
        return Result<void>::makeFailure(nodePos.error());
    }

    nodes.emplace_back(
        nodeData.substr(0, nodePos.value()),
        nodeData.substr(nodePos.value() + 1, hostPos.value() - nodePos.value() - 1),
        std::stoi(nodeData.substr(hostPos.value() + 1))
    );
    return Result<void>::makeSuccess();
}

ArgParser::Result<std::size_t> ArgParser::findCharPos(const std::string& s, char target)
{
    auto pos = s.find(target);
    if(pos == std::string::npos)
    {
        return Result<std::size_t>::makeFailure("Invalid peer format, expected nodeId@host:port");
    }
    return Result<std::size_t>::makeSuccess(pos);
}

ArgParser::Result<int> ArgParser::readInteger(const std::string& arg, int& index)
{
    if(index + 1 >= argc)
    {
        return Result<int>::makeFailure("Missing value for argument: " + arg);
    }
    try
    {
        return Result<int>::makeSuccess(std::stoi(argv[++index]));
    }
    catch(...)
    {
        return Result<int>::makeFailure("Invalid numeric value for argument: " + arg);
    }
}

ArgParser::Result<std::string> ArgParser::readString(const std::string& arg, int& index)
{
    if(index + 1 >= argc)
    {
        return Result<std::string>::makeFailure("Missing value for argument: " + arg);
    }
    return Result<std::string>::makeSuccess(argv[++index]);
}

} // namespace app::entrypoint::cli