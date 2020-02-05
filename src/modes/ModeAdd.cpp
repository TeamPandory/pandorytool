#include <iostream>
#include "ModeAdd.h"
#include <filesystem>
#include <map>
#include <tinyxml2.h>


std::string ModeAdd::padRomName(std::string string, const size_t size, const char character = ' ')
{
    if(size > string.size()) {
        string.insert(0, size - string.size(), character);
    }
    return string;
}



bool ModeAdd::validate() {
    if (!Fs::exists(sourceDir)) {
        std::cout << sourceDir << " does not exist " << std::endl;
        return false;
    }
    if (!Fs::exists(targetDir)) {
        std::cout << targetDir << " does not exist " << std::endl;
        return false;
    }
    return true;
}

ModeAdd::ModeAdd(string &sourceDir, string &targetDir) : sourceDir(sourceDir), targetDir(targetDir) {

}

// 1. Add games (MCGames)
int ModeAdd::main() {
    if (!validate()) {
        return 1;
    }
    createTargetDirectory();
    resetInstallFile();
    parseSourceDirectory();
    return 0;
}

void ModeAdd::parseSourceDirectory() {
    for (const auto &entry : filesystem::directory_iterator(this->sourceDir)) {
        std::string filePath = entry.path();
        std::string basename = Fs::basename(filePath);
        std::string gameListXml = filePath + "/gamelist.xml";
        if (Fs::exists(gameListXml)) {
            parseSourceGameXML(gameListXml);
        }
    }
}

std::string ModeAdd::convertSystemName(std::string system) {
    if (system == "Dreamcast") return "DC";
    if (system == "Game Boy Advance") return "GBA";
    if (system == "Game Boy Color") return "GBC";
    return "";
}

void ModeAdd::parseSourceGameXML(const string &gameListXml) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(gameListXml.c_str());
    std::string directory = Fs::dirname(gameListXml);
    tinyxml2::XMLElement *provider = doc.FirstChildElement("gameList")->FirstChildElement("provider");
    tinyxml2::XMLElement *gameList = doc.FirstChildElement("gameList");
    std::string system = provider->FirstChildElement("System")->GetText();
    int i = 1;
    for (tinyxml2::XMLElement *game = gameList->FirstChildElement("game");
         game != nullptr;
         game = game->NextSiblingElement("game")) {
        const char *romPath = game->FirstChildElement("path")->GetText();
        const char *romName = game->FirstChildElement("name")->GetText();
        std::string absoluteRomPath = directory + "/" + romPath;
        std::string shortSystemName = convertSystemName(system);
        if (!shortSystemName.empty()) {
            std::string targetRomName = shortSystemName + padRomName(std::to_string(i), 4, '0');
            std::string targetRomDir = targetDir + "/mcgames/" + targetRomName;
            copyRomToDestination(absoluteRomPath, targetRomDir);
            cout << "Found " << system << " ROM: " << romName << " [ " << Fs::basename(romPath) << " ]" << endl;
            i++;
        } else {
            cout << "Unknown system in source XML:" << system << endl;
        }
    }
}

// Checks subfolders within “source rom folder”.
// Copies both rom file – (and if available, mp4 file (from romsubfolder/media/videos))
// – to usbdevice:\mcgames\DC0001 (if dreamcast game) – check “ARSENAME” below for naming convention.
// Both DC0001.cdi and DC0001.mp4 should be within the mcgames/DC0001 folder.
// Template.txt and template.xml (from template file) should be then copied to the DC0001 folder with the
// following variables changed depending on system and game (see below)
// mcgames/install.txt file should then be appended with the “ARSENAME” (DC0001)                                                                                    repeat / loop process until all roms have been added.
void ModeAdd::copyRomToDestination(const std::string &rom, const std::string &destination) {
    if (!Fs::exists(destination)) {
        Fs::makeDirectory(destination);
    }
    std::string basename = Fs::basename(destination);
    std::string extension = Fs::getExtension(rom);
    Fs::copy(rom, destination + "/" + basename + extension);
}


void ModeAdd::resetInstallFile() {
    // remove mcgames/install.txt file if exists, open clear file
    string mcInstall = this->getMcGamesFolder() + "/install.txt";
    FILE *foo;
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



