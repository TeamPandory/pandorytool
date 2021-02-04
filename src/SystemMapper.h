#ifndef PANDORY_SYSTEMMAPPER_H
#define PANDORY_SYSTEMMAPPER_H
#include <string>
#include "SystemDefinition.h"

class SystemMapper {
public:

    SystemDefinition getSystemDefinition(const std::string& dir);

    std::string convertDirectoryNameToSystemName(std::string dir);

    int getScreenScraperId(const std::string& dir);

    void setConsoleColourBySystem(const std::string& dir);

    int getSystemSaveState(const std::string &dir);

    bool getSystemRenameFlag(const std::string& dir);

    int getGenre(const std::string& genre);
};


#endif //PANDORY_SYSTEMMAPPER_H
