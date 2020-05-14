#ifndef PANDORY_STICKS_H
#define PANDORY_STICKS_H

#include <map>
#include "../types.h"

class Sticks {
protected:
    std::map<std::string, downloadDefinition> sticks;

public:
    Sticks();
    downloadDefinition getStickByName(const std::string &name);
};


#endif //PANDORY_STICKS_H
