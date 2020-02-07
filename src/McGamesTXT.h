#ifndef PANDORY_MCGAMESTXT_H
#define PANDORY_MCGAMESTXT_H
#include <string>
#include "McGamesAbstract.h"

class McGamesTXT : public McGamesAbstract {
public:
    void generate(std::string filename) override;
};

#endif //PANDORY_MCGAMESTXT_H
