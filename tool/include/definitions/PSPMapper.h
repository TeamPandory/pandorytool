#pragma once
#include "types.h"
#include <map>

class PSPMapper
{
  protected:
    std::map<std::string, pspConfigGameDef> stockGames;
    std::map<std::string, downloadDefinition> controlFixes;

  public:
    PSPMapper();
    [[nodiscard]] const std::map<std::string, pspConfigGameDef>& getStockGames() const;
    [[nodiscard]] const std::map<std::string, downloadDefinition>& getControlFixes() const;
};