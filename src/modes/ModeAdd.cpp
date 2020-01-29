#include <iostream>
#include "ModeAdd.h"
#include <filesystem>
#include <map>
#include <tinyxml2.h>
using namespace std;

bool ModeAdd::validate() {
    if (!Fs::exists(sourceDir)) {
        cout << sourceDir << " does not exist " << endl;
        return false;
    }
    if (!Fs::exists(targetDir)) {
        cout << targetDir << " does not exist " << endl;
        return false;
    }
    return true;
}

ModeAdd::ModeAdd(string &sourceDir, string &targetDir) : sourceDir(sourceDir), targetDir(targetDir) {

}

int ModeAdd::main() {
    // 1. Add games (MCGames)
    if (!validate()) {
        return 1;
    }

    createTargetDirectory();
    resetInstallFile();

    cout << "fs start...";

    for (const auto & entry : filesystem::directory_iterator(sourceDir)) {
        string filePath = entry.path();
        string basename = Fs::basename(filePath);
        cout << filePath << endl;
        string gameListXml = filePath + "/gamelist.xml";
        if (Fs::exists(gameListXml)) {
            tinyxml2::XMLDocument doc;
            doc.LoadFile( gameListXml.c_str() );
            tinyxml2::XMLElement *provider = doc.FirstChildElement("gameList" )->FirstChildElement("provider" );
            tinyxml2::XMLElement *game = doc.FirstChildElement("gameList" )->FirstChildElement("game" );
            const char *system = provider->FirstChildElement("System")->GetText();
            const char *romPath = game->FirstChildElement("path")->GetText();
            const char *romName = game->FirstChildElement("name")->GetText();
            cout << "Found " << system << " rom:" << romName << " (" << romPath << ")" << endl;
            int x = 0;
        }
    }
    cout << "...fs end";
    return 0;
}

void ModeAdd::resetInstallFile() {
    // remove mcgames/install.txt file if exists, open clear file
    string mcInstall = this->getMcGamesFolder() + "/install.txt";
    FILE * foo;
    foo = fopen(mcInstall.c_str(), "w");
    fclose(foo);
}

bool ModeAdd::createTargetDirectory() {
    string mc = getMcGamesFolder();
    bool result = false;
    if (!Fs::exists(mc)) {
        cout << "Making " << mc << endl;
        result = Fs::makeDirectory(mc);
        if (!result) {
            cout << "Cannot create target" << endl;
        }
    }
    return result;
}

string ModeAdd::getMcGamesFolder() {
    string mc = this->targetDir + "/mcgames";
    return mc;
}



