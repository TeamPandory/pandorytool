#ifndef PANDORER_MODEADD_H
#define PANDORER_MODEADD_H

#include <string>
#include <tinyxml2.h>
#include <fstream>
#include "../Fs.h"
#include "../ConsoleColour.h"

class ModeAdd {
protected:
    ConsoleColour cc;
    std::ofstream installFile;
    std::string& sourceDir;
    std::string& targetDir;
    Fs fs;
    bool validate();
    bool createTargetDirectory();
    string getMcGamesFolder();
    void resetInstallFile();
    string getInstallFilePath();
    string pad(string string, const size_t size, const char character);
    void generateMcGamesMeta(tinyxml2::XMLElement *sourceGame, std::string shortSystemName, std::string romPath, std::string romFileName);

public:
    ModeAdd(std::string &sourceDir, std::string &targetDir);
    int main();
    void parseSourceDirectory();
    void parseSourceGameXML(const string &gameListXml);
    void copyRomToDestination(const string &rom, const string &destination);
    void copyRomVideoToDestination(const string &absoluteVideoPath, const string &destination);

    void openInstallFileHandle();
    void closeInstallFileHandle();
    void resetMcGamesFolder();
    string extractXMLText(tinyxml2::XMLElement *elem);
};

#endif //PANDORER_MODEADD_H
