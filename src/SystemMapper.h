#ifndef PANDORY_SYSTEMMAPPER_H
#define PANDORY_SYSTEMMAPPER_H
#include <string>

class SystemMapper {
public:
    static std::string convertDirectoryNameToSystemName(std::string dir);

    static void setConsoleColourBySystem(const std::string& dir);

    static int getSystemSaveState(const std::string &dir);

    static bool getSystemRenameFlag(const std::string& dir);

    static int getGenre(const std::string& genre);
};


#endif //PANDORY_SYSTEMMAPPER_H
