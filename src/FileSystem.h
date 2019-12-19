#ifndef PANDORER_FILESYSTEM_H
#define PANDORER_FILESYSTEM_H

#include <string>

class FileSystem {
public:
    static bool exists(std::string file);
    static bool makeDirectory(const std::string& dir);
};


#endif //PANDORER_FILESYSTEM_H
