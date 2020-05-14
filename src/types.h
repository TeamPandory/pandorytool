#ifndef PANDORY_TYPES_H
#define PANDORY_TYPES_H

#include <string>

struct pspConfigGameDef {
    int controlType = 0;
    int ppssppSettings = 0;
    int players = 0;
};

struct downloadDefinition {
    std::string name;
    std::string path;
    std::string url;
    std::string description;
};

#endif //PANDORY_TYPES_H
