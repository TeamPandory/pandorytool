#ifndef RESCRAPE_HASH_H
#define RESCRAPE_HASH_H

#include <string>

class Hash {
public:
    std::string md5_file(std::string filename);
};

#endif //RESCRAPE_HASH_H
