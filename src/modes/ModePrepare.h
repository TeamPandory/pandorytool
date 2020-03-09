#ifndef PANDORY_MODEPREPARE_H
#define PANDORY_MODEPREPARE_H


#include <string>

class ModePrepare {
protected:
    std::string& sourceDir;

public:
    explicit ModePrepare(std::string &sourceDir);
    int main();

    int mkdir(std::string systemType);
};


#endif //PANDORY_MODEPREPARE_H
