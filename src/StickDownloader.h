#ifndef PANDORY_STICKDOWNLOADER_H
#define PANDORY_STICKDOWNLOADER_H

#include "types.h"

class StickDownloader {

public:
    std::string download(const downloadDefinition &stick);
};

#endif //PANDORY_STICKDOWNLOADER_H
