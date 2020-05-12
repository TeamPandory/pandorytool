#ifndef PANDORY_STICKEXTRACTOR_H
#define PANDORY_STICKEXTRACTOR_H
#include <string>
#include "types.h"

class StickExtractor {
public:
    int exractToFolder(const stick &stick, std::string &tarPath, std::string &targetFolder);
};
#endif //PANDORY_STICKEXTRACTOR_H
