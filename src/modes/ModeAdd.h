#ifndef PANDORER_MODEADD_H
#define PANDORER_MODEADD_H

#include <string>
#include <tinyxml2.h>
#include <fstream>
#include "../Fs.h"
#include "../Console.h"
#include "../ScreenScraper.h"
#include "../Hash.h"
#include "../ScrapeService.h"
#include "../SystemMapper.h"

class ModeAdd {
protected:
    Fs fs;
    ScrapeService scrapeService;
    Console console;
    SystemMapper systemMapper;
    std::ofstream installFile;
    std::string& sourceDir;
    std::string& targetDir;
    std::string screenscrapeUsername = "meepmeepmeep";
    std::string screenscrapePassword = "meepmeepmeep";

    bool validate();
    bool createTargetDirectory();
    std::string getMcGamesFolder();
    void resetInstallFile();
    std::string getInstallFilePath();
    std::string pad(std::string string, const size_t size, const char character);
    void generateMcGamesMeta(tinyxml2::XMLElement *sourceGame, std::string system, std::string shortSystemName, std::string romPath, std::string targetRomName, std::string additionalRom);
    void parseRomFolder(const std::string& romFolder);

public:
    ModeAdd(std::string &sourceDir, std::string &targetDir);
    int main();
    void parseSourceDirectory();
    void parseSourceGameXML(const std::string &gameListXml);
    void copyRomToDestination(const std::string &rom, const std::string &destination, bool rename = true);
    void copyRomVideoToDestination(const std::string &absoluteVideoPath, const std::string &destination);
    void getScreenScraperDetails();
    void processRom();

    void openInstallFileHandle();
    void closeInstallFileHandle();
    void resetMcGamesFolder();
    std::string extractXMLText(tinyxml2::XMLElement *elem);

};

#endif //PANDORER_MODEADD_H
