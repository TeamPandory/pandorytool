#ifndef PANDORY_STICK_H
#define PANDORY_STICK_H


#include <string>
#include "../types.h"
#include "../EditionCheck.h"
#include "../ModeJailbreakStick.h"
#include "../definitions/Sticks.h"
#include "../ModeDXStick.h"

class ModeStick {
protected:
    std::string &stickType;
    std::string &targetDir;
    EditionCheck editionCheck;
    ModeJailbreakStick modeJailbreakStick;
    ModeDXStick modeDXStick;
    Sticks sticks;

public:
    ModeStick(std::string &stickType, std::string &targetDir);

    int main();

    int makeStick(const std::string &name);

    int makeStick(const downloadDefinition &stickData);
};


#endif //PANDORY_STICK_H
