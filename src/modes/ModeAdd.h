#ifndef PANDORER_MODEADD_H
#define PANDORER_MODEADD_H

#include <string>
#include <tinyxml2.h>
#include <fstream>
#include "../Fs.h"

class ModeAdd {
protected:
    std::ofstream installFile;
    std::string& sourceDir;
    std::string& targetDir;
    Fs fs;
    bool validate();
    bool createTargetDirectory();
    std::string getMcGamesFolder();
    void resetInstallFile();
    std::string getInstallFilePath();
    std::string pad(std::string string, const size_t size, const char character);
    void generateMcGamesMeta(tinyxml2::XMLElement *sourceGame, std::string system, std::string shortSystemName, std::string romPath, std::string romFileName);

public:
    ModeAdd(std::string &sourceDir, std::string &targetDir);
    int main();
    void parseSourceDirectory();
    void parseSourceGameXML(const std::string &gameListXml);
    void copyRomToDestination(const std::string &rom, const std::string &destination, bool rename = true);
    void copyRomVideoToDestination(const std::string &absoluteVideoPath, const std::string &destination);

    void openInstallFileHandle();
    void closeInstallFileHandle();
    void resetMcGamesFolder();
    std::string extractXMLText(tinyxml2::XMLElement *elem);
};

#endif //PANDORER_MODEADD_H
