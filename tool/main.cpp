#include "CommandLineArguments.h"
#include "PandoryTool.h"
#include <iostream>

int main(int argc, char* argv[])
{
    PandoryTool app(argc, argv);
    app.main(argc, argv);
    return 0;
}
