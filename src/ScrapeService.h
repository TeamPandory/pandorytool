#ifndef PANDORY_SCRAPESERVICE_H
#define PANDORY_SCRAPESERVICE_H
#include "Hash.h"
#include "ScreenScraper.h"
#include "SystemMapper.h"
#include "McGamesXML.h"

class ScrapeService {
protected:
    ScreenScraper screenScraper;
    SystemMapper systemMapper;
    Hash hash;
    std::string filename;
    std::string username = "meepmeepmeep";
    std::string password = "meepmeepmeep";
public:
    int scrapeRom();
    void setFilename(const std::string &filename);
    void setUsername(const std::string &scrapeUsername);
    void setPassword(const std::string &scrapePassword);
    McGamesXML convertXML();
};



#endif //PANDORY_SCRAPESERVICE_H
