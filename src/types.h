#ifndef PANDORY_TYPES_H
#define PANDORY_TYPES_H

#include <string>
#include <vector>

struct pspConfigGameDef {
    int controlType = 0;
    int ppssppSettings = 0;
    int players = 0;
    std::string ident = "";
};

struct downloadDefinition {
    std::string name;
    std::string path;
    std::string url;
    std::string description;
    std::string saveState0;
    std::string saveState1;
    std::string saveState2p;
    std::string keyRecord;
};

#endif //PANDORY_TYPES_H
