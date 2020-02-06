#ifndef PANDORER_MODEADD_H
#define PANDORER_MODEADD_H

#include <string>
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
    string padRomName(string string, const size_t size, const char character);
public:
    ModeAdd(std::string &sourceDir, std::string &targetDir);
    int main();
    void parseSourceDirectory();
    void parseSourceGameXML(const string &gameListXml);
    void copyRomToDestination(const string &rom, const string &destination);
    static string convertSystemName(string system);
    void addRomToInstallFile(string rom);

    void openInstallFileHandle();

    void closeInstallFileHandle();
};

#endif //PANDORER_MODEADD_H
