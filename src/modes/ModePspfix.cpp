#include <iostream>
#include "ModePspfix.h"
#include "../definitions/PSPMapper.h"
#include "../Fs.h"
#include "../StickDownloader.h"

#include "../types.h"
#include "../UserFolders.h"

int ModePspfix::checkStockPath() {
    std::string path = getStockPath();
    if (!Fs::exists(path)) {
        std::cout << path << " could not be found " << std::endl;
        std::cout << "Please install the PSP0000 stick using `pandory stick psp0000` in order to use pspstockfix."
                  << std::endl;
        return 1;
    }
    return 0;
}

int ModePspfix::stockFix() {

    UserFolders uf;
    std::string tempFolder = uf.getTemporaryFolder();

    stick backupStick = {
            "backup",
            "https://github.com/emuchicken/pandorytool/archive/stick-backup.tar.gz"
    };
    StickDownloader sdl;
    sdl.download(backupStick);

    return EXIT_SUCCESS;


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
