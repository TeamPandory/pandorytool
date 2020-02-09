#ifndef PANDORY_SYSTEMMAPPER_H
#define PANDORY_SYSTEMMAPPER_H
#include <string>

class SystemMapper {
public:
    static std::string convertDirectoryNameToSystemName(std::string dir);

    static int getConsoleColour(std::string systemName);
};


#endif //PANDORY_SYSTEMMAPPER_H
