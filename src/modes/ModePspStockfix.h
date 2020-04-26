#ifndef PANDORY_STOCKFIX_H
#define PANDORY_STOCKFIX_H

#include <string>
#include "../types.h"

class ModePspStockfix {
protected:
    std::string& targetDir;

public:
    explicit ModePspStockfix(std::string &targetDir);
    int patchControlFolder(std::string source, std::string target, pspConfigGameDef gameDef);
    int main();
};

#endif //PANDORY_STOCKFIX_H
