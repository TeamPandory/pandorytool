#ifndef PANDORY_SCRAPESERVICE_H
#define PANDORY_SCRAPESERVICE_H
#include "Hash.h"
#include "ScreenScraper.h"
#include "SystemMapper.h"
#include "McGamesXML.h"
#include "ScreenScraperXML.h"
#include "McGamesTXT.h"

class ScrapeService {
protected:
    SystemMapper systemMapper;
    Hash hash;
    ScreenScraperXML screenScraperXml;
protected:
    std::string filename;
    std::string username;
    std::string password;
public:
    int scrapeRom();
    void setFilename(const std::string &filePath);
    void setUsername(const std::string &scrapeUsername);
    void setPassword(const std::string &scrapePassword);
    ScreenScraperXML * getScreenScraperXml();
    McGamesXML getMcGamesXML();
    McGamesTXT getMcGamesTXT();
};
#endif //PANDORY_SCRAPESERVICE_H
