#ifndef PANDORER_MODEADD_H
#define PANDORER_MODEADD_H

#include <string>
#include "../FileSystem.h"

class ModeAdd {
protected:
    std::string& sourceDir;
    std::string& targetDir;
    FileSystem fs;
public:
    ModeAdd(std::string &sourceDir, std::string &targetDir);
    int main();


protected:
    bool validate();
public:
};

#endif //PANDORER_MODEADD_H
