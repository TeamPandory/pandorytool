#include "ScrapeService.h"
#include "McGamesTXT.h"
#include "ScreenScraperXML.h"
#include <iostream>
#include <thread>

int ScrapeService::scrapeRom()
{
    std::string md5 = hash.md5_file(filename);
    ScreenScraper screenScraper;
    screenScraper.setUsername(username);
    screenScraper.setPassword(password);
    screenScraper.setRomHash(md5);
    screenScraper.setRomFilename(filename);
    screenScraper.setDestinationFolder("scrapes");
    bool keepGoing = true;
    int limit = 0;
    while (keepGoing && limit < 5)
    {
        screenScraper.setScraperSystemId(systemMapper.getScreenScraperId(Fs::basename(Fs::dirname(filename))));
        int result = screenScraper.scrape();
        if (result != 500)
        {
            keepGoing = false;
        }
        else
        {
            if (limit == 0)
                std::cout << std::endl;
            std::cout << " - Scraper service returned an error. Retrying in 5 seconds..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            limit++;
        }
    }
    if (screenScraper.isValid())
    {
        std::string xmlPath = screenScraper.dumpXML();
        if (!xmlPath.empty())
        {
            bool valid = screenScraperXml.load(xmlPath);
            if (valid)
            {
                screenScraper.downloadVideo();
                screenScraper.downloadScreenshot();
            }
        }
        return 0;
    }
    return 1;
}

McGamesXML ScrapeService::getMcGamesXML()
{
    const std::string& dirname = Fs::dirname(filename);
    const std::string& baseDirName = Fs::basename(dirname);
    SystemDefinition sysDef = systemMapper.getSystemDefinition(baseDirName);
    McGamesXML mcXML;
    mcXML.setEmulatorId(std::to_string(sysDef.getId()));
    mcXML.setEmulatorLoad(std::to_string(sysDef.getLoadTime()));
    std::string romTitle = screenScraperXml.getRomName();
    mcXML.setRomTitle(romTitle);
    mcXML.setPlayers(screenScraperXml.getPlayers());
    mcXML.setRomDescription(screenScraperXml.getDescription());
    mcXML.setLanguage("EN");
    mcXML.setYear(screenScraperXml.getYear());
    mcXML.setGenre(systemMapper.getGenre(screenScraperXml.getGenre()));
    mcXML.setSaveState(systemMapper.getSystemSaveState(baseDirName));
    mcXML.setRomDeveloper(screenScraperXml.getDeveloper());
    mcXML.setConsole(screenScraperXml.getConsole());
    mcXML.setRomTitleSuffix(screenScraperXml.getSuffix());
    return mcXML;
}

McGamesTXT ScrapeService::getMcGamesTXT()
{
    const std::string& dirname = Fs::dirname(filename);
    const std::string& baseDirName = Fs::basename(dirname);
    SystemDefinition sysDef = systemMapper.getSystemDefinition(baseDirName);
    McGamesTXT mcTXT;
    mcTXT.setEmulatorId(std::to_string(sysDef.getId()));
    mcTXT.setEmulatorLoad(std::to_string(sysDef.getLoadTime()));
    mcTXT.setRomTitle(screenScraperXml.getRomName());
    mcTXT.setRomDescription(screenScraperXml.getDescription());
    mcTXT.setLanguage("EN");
    mcTXT.setYear(screenScraperXml.getYear());
    mcTXT.setGenre(systemMapper.getGenre(screenScraperXml.getGenre()));
    mcTXT.setRomDeveloper(screenScraperXml.getDeveloper());
    return mcTXT;
}

void ScrapeService::setUsername(const std::string& scrapeUsername)
{
    ScrapeService::username = scrapeUsername;
}

void ScrapeService::setPassword(const std::string& scrapePassword)
{
    ScrapeService::password = scrapePassword;
}

void ScrapeService::setFilename(const std::string& filePath)
{
    ScrapeService::filename = filePath;
}

ScreenScraperXML* ScrapeService::getScreenScraperXml()
{
    return &screenScraperXml;
}
