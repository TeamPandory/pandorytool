#include "CommandLineArguments.h"
#include "PandoryTool.h"
#include "modes/ModeAdd.h"

PandoryTool::PandoryTool(int i, char **pString) {
    args = CommandLineArguments(i, pString);
}

int PandoryTool::main() {
    std::cout << "Pandora 3D Add Game Utility, by emuchicken & dajoho" << std::endl;
    if (args.getArgumentCount() == 1) {
        usage();
        return 1;
    }
    std::string mode = args.getArgument(1);
    if (mode == "add") {
        return add();
    }
    return 0;
}

void PandoryTool::usage() {
    std::cout << "Usage: " << std::endl;
    std::cout << "\tpandory add <sourceDir> <destDir>" << std::endl;
}

int PandoryTool::add() {
    std::string sourceDir = args.getArgument(2);
    std::string targetDir = args.getArgument(3);
    if (sourceDir.empty() || targetDir.empty()) {
        usage();
        return 1;
    }
    ModeAdd add(sourceDir, targetDir);
    add.main();
    return 0;
}
