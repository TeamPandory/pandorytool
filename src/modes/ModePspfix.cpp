#include <iostream>
#include <fstream>
#include "ModePspfix.h"
#include "../definitions/PSPMapper.h"
#include "../Fs.h"
#include "../StickDownloader.h"
#include "../types.h"
#include "../UserFolders.h"
#include "../StickExtractor.h"

bool ModePspfix::checkStockPath() {
    std::string path = getStockPath();
    if (!Fs::exists(path)) {
        std::cout << path << " could not be found " << std::endl;
        std::cout << "Please run `pandory pspfix stage1`, install the PSP injector on your Pandora console" << std::endl
                  << "and then insert your SD card into drive " << targetDir << " in order to fix stock games."
                  << std::endl;
        return false;
    }
    return true;
}

int ModePspfix::stockFix() {
    UserFolders uf;
    std::string tempFolder = uf.getTemporaryFolder();
    std::cout << "Attempting to fix stock PSP game controls..." << std::endl;
    if (!checkStockPath()) {
        return 1;
    }
    std::string path = getStockPath();
    patchControlFolder(path, path, pspConfigGameDef{0, 2, 1});

    auto pspMapper = new PSPMapper;
    auto pspGames = pspMapper->getStockGames();
    std::map<std::string, pspConfigGameDef>::iterator it;
    for (it = pspGames.begin(); it != pspGames.end(); it++) {
        std::string romPath = targetDir + "/games/data/family/" + it->first;
        if (Fs::exists(romPath) && it->second.players == 1) {
            std::cout << "Fixing settings/controls for: " << it->first << std::endl;
            patchControlFolder(path, romPath + "/", it->second);
        } else {
            std::cout << "Skipping ROM settings fix: " << it->first << std::endl;
        }
    }
    return 0;
}

int ModePspfix::otherFix() {
    std::cout << "Attempting to fix non-stock PSP game controls..." << std::endl;
    if (!checkStockPath()) {
        return 1;
    }

    std::string romsPath = targetDir + "/games/data/family/";
    std::string path = getStockPath();
    patchControlFolder(path, path, pspConfigGameDef{0, 2, 1});

    for (const auto &entry : std::filesystem::directory_iterator(romsPath)) {
        std::string romFolder = Fs::basename(entry.path().string());
        if (romFolder.substr(0, 3) == "PSP" && romFolder != "PSP0000") {
            std::cout << romFolder << std::endl;
            patchControlFolder(path, entry.path().string() + "/", pspConfigGameDef{0, 1, 1});
        }
    }
    return 0;
}

ModePspfix::ModePspfix(std::string &targetDir) : targetDir(targetDir) {

}

int ModePspfix::patchControlFolder(const std::string &source, const std::string &target, pspConfigGameDef gameDef) {
    Fs::makeDirectory(target + "PSP");
    Fs::makeDirectory(target + "PSP/SYSTEM");
    Fs::copy(source + "controls" + std::to_string(gameDef.controlType) + ".ini", target + "PSP/SYSTEM/controls.ini");
    Fs::copy(source + "ppsspp" + std::to_string(gameDef.ppssppSettings) + ".ini", target + "PSP/SYSTEM/ppsspp.ini");
    return 0;
}

std::string ModePspfix::getStockPath() {
    std::string path = targetDir + "/games/data/family/PSP0000/";
    return path;
}

int ModePspfix::stage1() {
    std::cout << "Installing PSP injector to " << targetDir << std::endl;

    if (!Fs::exists(targetDir)) {
        std::cout << targetDir << " does not exist, exiting." << std::endl;
        return 1;
    }

    std::string mcGames = targetDir + "/mcgames/";
    std::string pspRomFolder = mcGames + "PSP0000";
    Fs::makeDirectory(mcGames);
    Fs::makeDirectory(pspRomFolder);
    if (!Fs::exists(mcGames)) {
        std::cout << "Cannot create " << targetDir << ", exiting." << std::endl;
        return 1;
    }

    std::ofstream installFile;
    installFile.open(mcGames+"install.txt");
    installFile << "PSP0000" << std::endl;
    installFile.close();

    StickDownloader stickDl;
    StickExtractor stickExt;
    PSPMapper pm;
    std::map<std::string, downloadDefinition>balls = pm.getControlFixes();
    std::map<std::string, downloadDefinition>::iterator it;
    int result = 0;
    for (it = balls.begin(); it != balls.end(); it++) {
        std::string stickName = it->second.name;
        downloadDefinition def = it->second;
        std::cout << "Downloading " << def.name << " control files..." << std::endl;
        std::string tarGz = stickDl.download(def);
        if (!Fs::exists(tarGz)) {
            std::cout << "Could not download " << stickName << ", exiting." << std::endl;
        }
        result = stickExt.exractToFolder(def, tarGz, pspRomFolder);
        if (result == 1) {
            std::cout << "There was a problem extracting " << stickName << ", exiting." << std::endl;
        }
    }
    return result;
}
