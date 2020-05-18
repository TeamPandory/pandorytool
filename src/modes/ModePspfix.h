#ifndef PANDORY_STOCKFIX_H
#define PANDORY_STOCKFIX_H

#include <string>
#include "../types.h"

class ModePspfix {
protected:
    std::string& targetDir;
    std::string stockPath = "/games/data/family/PSP0000/";
    std::string getStockPath();
public:
    explicit ModePspfix(std::string &targetDir);
    int patchControlFolder(const std::string& source, const std::string& target, pspConfigGameDef gameDef);
    int otherFix();
    int stockFix();
    int stage1();
    int stage2();

    bool checkStockPath();
};

#endif //PANDORY_STOCKFIX_H
