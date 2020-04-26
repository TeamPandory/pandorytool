#ifndef PANDORY_STOCKFIX_H
#define PANDORY_STOCKFIX_H

#include <string>
#include "../types.h"

class ModePspfix {
protected:
    std::string& targetDir;

public:
    explicit ModePspfix(std::string &targetDir);
    int patchControlFolder(std::string source, std::string target, pspConfigGameDef gameDef);
    int stock();
};

#endif //PANDORY_STOCKFIX_H
