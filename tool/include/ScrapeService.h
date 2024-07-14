#pragma once
#include "Hash.h"
#include "McGamesTXT.h"
#include "McGamesXML.h"
#include "ScreenScraper.h"
#include "ScreenScraperXML.h"
#include "SystemMapper.h"

class ScrapeService
{
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
    void setFilename(const std::string& filePath);
    void setUsername(const std::string& scrapeUsername);
    void setPassword(const std::string& scrapePassword);
    ScreenScraperXML* getScreenScraperXml();
    McGamesXML getMcGamesXML();
    McGamesTXT getMcGamesTXT();
};