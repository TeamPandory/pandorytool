#ifndef PANDORY_PSPMAPPER_H
#define PANDORY_PSPMAPPER_H

#include <map>
#include "../types.h"


class PSPMapper {
    protected:
        std::map<std::string, pspConfigGameDef> stockGames;
        std::map<std::string, pspConfigTwoPlayer> stockTwoPlayerCodes;

public:
    PSPMapper();

    [[nodiscard]] const std::map<std::string, pspConfigGameDef> &getStockGames() const;
    [[nodiscard]] const std::map<std::string, pspConfigTwoPlayer> &getTwoPlayerCodes() const;

};


#endif //PANDORY_PSPMAPPER_H
