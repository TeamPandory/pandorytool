#ifndef PANDORY_STICKS_H
#define PANDORY_STICKS_H

#include <map>
#include "../types.h"

class Sticks {
protected:
    std::map<std::string, stick> sticks;

public:
    Sticks();
    stick getStickByName(const std::string &stickName);
};


#endif //PANDORY_STICKS_H
