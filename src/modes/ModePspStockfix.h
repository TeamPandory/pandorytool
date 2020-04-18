#ifndef PANDORY_STOCKFIX_H
#define PANDORY_STOCKFIX_H


#include <string>

class ModePspStockfix {
protected:
    std::string& targetDir;

public:
    explicit ModePspStockfix(std::string &targetDir);
    int main();

};


#endif //PANDORY_STOCKFIX_H
