#include <string>
#include "CommandLineArguments.h"

CommandLineArguments::CommandLineArguments(int argc, char *argv[]) {
    argumentCount = argc;
    argumentPointers = argv;

}

int CommandLineArguments::getArgumentCount() {
    return argumentCount;
}

std::string CommandLineArguments::getArgument(int n) {
    for (int i = 0; i < argumentCount; ++i) {
        if (i == n) {
            return std::string(argumentPointers[i]);
        }
    }
    return std::string();
}

std::string CommandLineArguments::getPathArgument(int n) {
    std::string arg = getArgument(n);
    if (!arg.empty()) {
        if (arg.substr(-1) == ":") {
            arg += "/";
        }
    }
    return std::string();
}




