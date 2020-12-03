#include <iostream>
#include "ScrapeService.h"
#include "ScreenScraperXML.h"

int ScrapeService::scrapeRom() {
    std::string md5 = hash.md5_file(filename);
    screenScraper.setUsername(username);
    screenScraper.setPassword(password);
    screenScraper.setRomHash(md5);
    screenScraper.setRomFilename(filename);
    screenScraper.setDestinationFolder("scrapes");
    screenScraper.scrape();
    if (screenScraper.isValid()) {
        std::string xmlPath = screenScraper.dumpXML();
        if (!xmlPath.empty()) {
            ScreenScraperXML screenScraperXml;
            bool valid = screenScraperXml.load(xmlPath);
            if (valid) {
                std::cout << "- identified as " << screenScraperXml.getRomName() << std::endl;
                //screenScraper.downloadAll();
            }
        }
        return 0;
    }
    return 1;
}

McGamesXML ScrapeService::convertXML() {
    std::string directoryName = Fs::basename(Fs::dirname(filename));

    SystemDefinition sysDef = systemMapper.getSystemDefinition(directoryName);

    McGamesXML mcXML;
    mcXML.setEmulatorId(std::to_string(sysDef.getId()));
    mcXML.setEmulatorLoad(std::to_string(sysDef.getLoadTime()));
    return mcXML;
    /*
    mcXML.setRomTitle(name);
    mcXML.setRomFileName(romFileName);
    mcXML.setRomShortId(targetRomName);
    mcXML.setPlayers(players);
    mcXML.setRomDescription(desc);
    mcXML.setLanguage("EN"); //TODO is this always true?
    mcXML.setYear(year);
    mcXML.setGenre(SystemMapper::getGenre(genre));
    mcXML.setRomDeveloper(developer);
    mcXML.setRomPath(relativeRomPath);
    mcXML.setSaveState(SystemMapper::getSystemSaveState(system));
     */
}

void ScrapeService::setUsername(const std::string &scrapeUsername) {
    ScrapeService::username = scrapeUsername;
}

void ScrapeService::setPassword(const std::string &scrapePassword) {
    ScrapeService::password = scrapePassword;
}

void ScrapeService::setFilename(const std::string &filename) {
    ScrapeService::filename = filename;
}


