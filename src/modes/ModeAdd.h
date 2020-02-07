#ifndef PANDORER_MODEADD_H
#define PANDORER_MODEADD_H

#include <string>
#include <tinyxml2.h>
#include <fstream>
#include "../Fs.h"
using namespace std;

class ModeAdd {
protected:
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
    void streamXMLGameData(tinyxml2::XMLElement *sourceDocument, std::string shortSystemName, std::string romPath, std::string romName);

public:
    ModeAdd(std::string &sourceDir, std::string &targetDir);
    int main();
    void parseSourceDirectory();
    void parseSourceGameXML(const string &gameListXml);
    void copyRomToDestination(const string &rom, const string &destination);
    static string convertSystemName(string system);

    void openInstallFileHandle();

    void closeInstallFileHandle();

    void resetMcGamesFolder();

    string extractXMLText(tinyxml2::XMLElement *elem);
};

#endif //PANDORER_MODEADD_H
