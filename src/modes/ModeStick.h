#ifndef PANDORY_STICK_H
#define PANDORY_STICK_H


#include <string>
#include "../types.h"

class ModeStick {
protected:
    std::string &stickType;
    std::string &targetDir;

public:
    ModeStick(std::string &stickType, std::string &targetDir);

    int main();

    int makeStick(const std::string &name);

    int makeStick(downloadDefinition stickData);
};


#endif //PANDORY_STICK_H
