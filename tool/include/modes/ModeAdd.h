#pragma once
#include "Console.h"
#include "Fs.h"
#include "Hash.h"
#include "ScrapeService.h"
#include "SystemMapper.h"
#include <fstream>
#include <string>
#include <tinyxml2.h>

class ModeAdd
{
  protected:
    Fs fs;
    ScrapeService scrapeService;
    Console console;
    Hash hash;
    SystemMapper systemMapper;
    std::ofstream installFile;
    std::string& sourceDir;
    std::string& targetDir;
    std::string screenscrapeUsername;
    std::string screenscrapePassword;

    bool validate();
    bool createTargetDirectory();
    std::string getMcGamesFolder();
    void resetInstallFile();
    std::string getInstallFilePath();
    std::string pad(std::string string, const size_t size, const char character);
    void parseRomFolder(const std::string& romFolder);

  public:
    ModeAdd(std::string& sourceDir, std::string& targetDir);
    int main();
    void parseSourceDirectory();
    void copyRomToDestination(const std::string& rom, const std::string& destination, bool rename = true);
    void copyRomVideoToDestination(const std::string& absoluteVideoPath, const std::string& destination);
    void getScreenScraperDetails();
    McGamesXML processRom(const std::string& romFolder, const std::string& filePath);

    void openInstallFileHandle();
    void closeInstallFileHandle();
    void resetMcGamesFolder();
    std::string extractXMLText(tinyxml2::XMLElement* elem);

    bool checkSharewareLimit(int i);

    void showRomIdentification(const std::string& system, McGamesXML& mcGamesXml);

    std::string& calculateRomName(int i, const std::string& system, const std::string& filePath, McGamesXML& mcGamesXml,
                                  const std::string& shortSystemName, std::string& targetRomName);

    std::string getRomSuffix(const std::string& romFilename);
};