#ifndef PANDORER_MODEADD_H
#define PANDORER_MODEADD_H

#include <string>
#include "../Fs.h"
using namespace std;

class ModeAdd {
protected:
    std::string& sourceDir;
    std::string& targetDir;
    Fs fs;
    bool validate();
    bool createTargetDirectory();
    string getMcGamesFolder();
    void resetInstallFile();
public:
    ModeAdd(std::string &sourceDir, std::string &targetDir);
    int main();

    void parseSourceDirectory();

    void parseSourceGameXML(const string &gameListXml);

    void copyRomToDestination(const string &rom, const string &destination);

    static string convertSystemName(string system);
};

#endif //PANDORER_MODEADD_H
