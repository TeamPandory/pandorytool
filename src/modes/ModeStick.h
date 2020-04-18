#ifndef PANDORY_STICK_H
#define PANDORY_STICK_H


#include <string>

class ModeStick {
protected:
    std::string &stickType;
    std::string &targetDir;

public:
    ModeStick(std::string &stickType, std::string &targetDir);

    int main();

    int jailbreak();

    int backup();
};


#endif //PANDORY_STICK_H
