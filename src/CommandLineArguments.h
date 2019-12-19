#ifndef TESTC_COMMANDLINEARGUMENTS_H
#define TESTC_COMMANDLINEARGUMENTS_H

#include <string>
#include <iostream>
class CommandLineArguments {
protected:
    int argumentCount;
    char **argumentPointers;
public:
    CommandLineArguments(int argc, char *argv[]);
    int getArgumentCount();
    std::string getArgument(int n);

};

#endif //TESTC_COMMANDLINEARGUMENTS_H
