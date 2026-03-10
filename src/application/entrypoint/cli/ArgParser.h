#pragma once

#include "application/entrypoint/AppConfig.h"
#include "core/types/BasicResult.h"

namespace app::entrypoint::cli {

class ArgParser
{
    template <typename T>
    using Result = core::types::BasicResult<T>;

public:
    explicit ArgParser(int argc, char** argv);
    Result<AppConfig> parse();

private:
    Result<void> parseNodes(std::vector<domain::cluster::model::NodeInfo>& nodes, int& index);
    Result<std::size_t> findCharPos(const std::string& s, char target);
    Result<int> readInteger(const std::string& arg, int& index);
    Result<std::string> readString(const std::string& arg, int& index);

    int argc;
    char** argv;
};

} // namespace app::entrypoint::cli