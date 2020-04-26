#ifndef PANDORY_PSPMAPPER_H
#define PANDORY_PSPMAPPER_H

#include <map>
#include "../types.h"


class PSPMapper {
    protected:
        std::map<std::string, pspConfigGameDef> stockGames;

public:
    PSPMapper();

    const std::map<std::string, pspConfigGameDef> &getStockGames() const;
};


#endif //PANDORY_PSPMAPPER_H
