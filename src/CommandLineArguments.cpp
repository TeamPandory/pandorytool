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
        int len = arg.length();
        std::string end = arg.substr(len-1, 1);
        if (end == ":") {
            arg += "/";
        }
        return arg;
    }
    return std::string();
}




