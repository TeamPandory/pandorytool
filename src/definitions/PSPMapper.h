#ifndef PANDORY_PSPMAPPER_H
#define PANDORY_PSPMAPPER_H

#include <map>
#include "../types.h"


class PSPMapper {
    protected:
        std::map<std::string, pspConfigGameDef> stockGames;
        std::map<std::string, downloadDefinition> controlFixes;
public:
    PSPMapper();
    [[nodiscard]] const std::map<std::string, pspConfigGameDef> &getStockGames() const;
    [[nodiscard]] const std::map<std::string, downloadDefinition> &getControlFixes() const;
};


#endif //PANDORY_PSPMAPPER_H
