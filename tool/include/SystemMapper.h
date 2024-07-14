#pragma once
#include "SystemDefinition.h"
#include <string>

class SystemMapper
{
  public:
    SystemDefinition getSystemDefinition(const std::string& dir);

    std::string convertDirectoryNameToSystemName(std::string dir);

    int getScreenScraperId(const std::string& dir);

    void setConsoleColourBySystem(const std::string& dir);

    int getSystemSaveState(const std::string& dir);

    bool getSystemRenameFlag(const std::string& dir);

    int getGenre(const std::string& genre);
};