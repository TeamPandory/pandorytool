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

ModeAdd::ModeAdd(std::string &sourceDir, std::string &targetDir) : sourceDir(sourceDir), targetDir(targetDir) {

}

// 1. Add games (MCGames)
int ModeAdd::main() {
    if (!validate()) {
        return 1;
    }
    createTargetDirectory();
    resetInstallFile();
    resetMcGamesFolder();
    parseSourceDirectory();
    return 0;
}

void ModeAdd::parseSourceDirectory() {
    openInstallFileHandle();
    for (const auto &entry : filesystem::directory_iterator(this->sourceDir)) {
        std::string filePath = entry.path().string();
        std::string basename = Fs::basename(filePath);
        std::string gameListXml = filePath + "/gamelist.xml";
        if (Fs::exists(gameListXml)) {
            parseSourceGameXML(gameListXml);
        }
    }
    closeInstallFileHandle();
}

std::string ModeAdd::convertSystemName(std::string system) {
    if (system == "dreamcast") return "DC";
    if (system == "gba") return "GBA";
    if (system == "gbc") return "GBC";
    if (system == "megadrive") return "MD";
    if (system == "n64") return "N64";
    if (system == "playstation") return "PS";
    if (system == "psp") return "PSP";
    if (system == "snes") return "SNES";
    //if (system == "Family Computer") return "NES";
    //if (system == "TurboGrafx-16") return "PCE";
    //...MAME...
    //...
    return "";
}

void ModeAdd::openInstallFileHandle()
{
    installFile.open(getInstallFilePath().c_str());
}

void ModeAdd::closeInstallFileHandle()
{
    installFile.close();
}

void ModeAdd::parseSourceGameXML(const std::string &gameListXml) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(gameListXml.c_str());
    std::string directory = Fs::dirname(gameListXml);
    tinyxml2::XMLElement *gameList = doc.FirstChildElement("gameList");
    tinyxml2::XMLElement *provider = gameList->FirstChildElement("provider");
    std::string system = Fs::basename(directory);
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
            std::string floppy = "\U0001F4BE";
            std::string cdrom = "\U0001F4C0";
            int filesize = Fs::filesize(absoluteRomPath) / 1024 / 1024;
            std::string icon = (filesize <= 50) ? floppy : cdrom;
            if (getenv("COMSPEC") != nullptr) {
                std::string comspec = getenv("COMSPEC");
                if (comspec.find("cmd.exe") != std::string::npos) {
                    icon = "-";
                }
            }
            std::cout << icon << " Found "
                 << extractXMLText(provider->FirstChildElement("System"))
                 << " ROM: " << romName << " [ " << Fs::basename(romPath)
                 << " ]" << endl;
            copyRomToDestination(absoluteRomPath, targetRomDir);
            installFile << targetRomName << std::endl;
            streamXMLGameData(game, shortSystemName, targetRomDir, targetRomName);
            i++;
        } else {
            cout << "Unknown system detected in source folder: " << system << endl;
        }
    }
}


// Checks subfolders within “source rom folder”.
// Copies both rom file – (and if available, mp4 file (from romsubfolder/media/videos))
// – to usbdevice:\mcgames\DC0001 (if dreamcast game) – check “ARSENAME” below for naming convention.
// Both DC0001.cdi and DC0001.mp4 should be within the mcgames/DC0001 folder.
// Template.txt and template.xml (from template file) should be then copied to the DC0001 folder with the
// following variables changed depending on system and game (see below)
// install.txt file should then be appended with the “ARSENAME” (DC0001)
// repeat / loop process until all roms have been added.
void ModeAdd::copyRomToDestination(const std::string &rom, const std::string &destination) {
    if (!Fs::exists(destination)) {
        Fs::makeDirectory(destination);
    }
    std::string basename = Fs::basename(destination);
    std::string extension = Fs::getExtension(rom);
    Fs::copy(rom, destination + "/" + basename + extension);
}

// remove install.txt file if exists, open clear file
void ModeAdd::resetInstallFile() {
    std::string mcInstall = getInstallFilePath();
    FILE *foo;
    foo = fopen(mcInstall.c_str(), "w");
    fclose(foo);
}

void ModeAdd::resetMcGamesFolder() {
    std::string mgGamesFolder = getMcGamesFolder();
    Fs::remove(getMcGamesFolder());
    Fs::makeDirectory(getMcGamesFolder());
}

string ModeAdd::getInstallFilePath() {
    string mcInstall = this->targetDir + "/install.txt";
    return mcInstall;
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

std::string ModeAdd::extractXMLText(tinyxml2::XMLElement *elem)
{
    if (elem->GetText() != nullptr) {
        return elem->GetText();
    }
    return std::string();
}

void ModeAdd::streamXMLGameData(tinyxml2::XMLElement *sourceGame, std::string shortSystemName, std::string romPath, std::string romName) {
    std::string targetXMLFile = romPath + "/" + romName + ".xml";
    std::FILE* fp = std::fopen(targetXMLFile.c_str(), "w");
    tinyxml2::XMLPrinter xml(fp );
    xml.PushDeclaration("xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"");

    // # Game
    xml.OpenElement("game" );
    xml.PushAttribute("emulator", shortSystemName.c_str());
    xml.PushAttribute("name", romName.c_str());
    // ## Information
    xml.OpenElement("information" );
    // ### Description
    xml.OpenElement("description");
    std::string desc = extractXMLText(sourceGame->FirstChildElement("desc"));
    xml.PushText(desc.c_str());
    xml.CloseElement();
    xml.OpenElement("cloneof" );
    xml.CloseElement();
    xml.OpenElement("language" );
    xml.PushText("EN");
    xml.CloseElement();
    xml.OpenElement("year" );
    xml.CloseElement();
    xml.OpenElement("manufacturer" );
    xml.CloseElement();
    xml.OpenElement("player" );
    xml.CloseElement();
    xml.OpenElement("genre" );
    xml.CloseElement();
    xml.OpenElement("bootleg" );
    xml.CloseElement();
    // ### /Description
    xml.CloseElement(); // ## /Information

    // ### File
    xml.OpenElement("file" );
    xml.OpenElement("rom" );
    xml.CloseElement();
    xml.CloseElement();
    // ### /File

    // ### Translation
    xml.OpenElement("translation" );
    xml.OpenElement("string" );
    xml.PushAttribute("language", "EN");
    xml.OpenElement("name" );
    xml.CloseElement(); // name
    xml.OpenElement("detail" );
    xml.CloseElement(); // detail
    xml.CloseElement(); // string
    xml.CloseElement(); // translation
    // ### /File

    // ### Config
    xml.OpenElement("config" );
    xml.OpenElement("flag" );
    xml.PushText(0);
    xml.CloseElement(); // flag
    xml.OpenElement("load_time" );
    xml.PushText("ARSELOAD"); //TODO
    xml.CloseElement(); // load_time

    xml.OpenElement("free_play" );
    xml.PushText(true); //TODO
    xml.CloseElement(); // free_play

    xml.OpenElement("save_state" );
    xml.PushText(true); //TODO
    xml.CloseElement(); // save_state

    xml.OpenElement("start_directly" );
    xml.PushText(true); //TODO
    xml.CloseElement(); // start_directly

    xml.CloseElement(); // config
    // ### /Config

    xml.CloseElement(); // game
}



