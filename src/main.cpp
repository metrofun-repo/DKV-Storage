#include "application/entrypoint/App.h"
#include "application/entrypoint/cli/ArgParser.h"

int main(int argc, char* argv[])
{
    app::entrypoint::cli::ArgParser parser(argc, argv);
    auto parseResult = parser.parse();
    if(!parseResult.hasValue())
    {
        std::cout << "Failed to parse agrs: " << parseResult.error().details << std::endl;
        std::cout << "Press Enter to exit ...";
        std::string _;
        std::getline(std::cin, _);
        return 0;
    }
    app::entrypoint::App app(parseResult.value());

    app.run();

    return 0;
}