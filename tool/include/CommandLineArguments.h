#pragma once
#include <string>
class CommandLineArguments
{
  protected:
    int argumentCount;
    char** argumentPointers;

  public:
    CommandLineArguments(int argc, char* argv[]);
    int getArgumentCount();
    std::string getArgument(int n);

    std::string getPathArgument(int n);
};