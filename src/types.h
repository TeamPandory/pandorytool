#ifndef PANDORY_TYPES_H
#define PANDORY_TYPES_H

#include <string>

struct pspConfigGameDef {
    int controlType = 0;
    int ppssppSettings = 0;
    int players = 0;
};

struct pspConfigTwoPlayer {
    std::string pspGameCode;
};

struct stick {
    std::string stickName;
    std::string stickUrl;
};

#endif //PANDORY_TYPES_H
