#include <iostream>
#include "ModePspStockfix.h"
#include "../definitions/PSPMapper.h"
#include "../Fs.h"

int ModePspStockfix::main() {
    std::cout << "Attempting to fix stock PSP game controls..." << std::endl;

    std::string path = targetDir + "/games/data/family/PSP0000/";
    if (!Fs::exists(path)) {
        std::cout << path << " could not be found " << std::endl;
        std::cout << "Please install the PSP0000 game using `pandory add` in order to use pspstockfix." << std::endl;
        return 1;
    }

    patchControlFolder(path, path, pspConfigGameDef{0, 2, 1});

    auto pspMapper = new PSPMapper;
    auto pspGames = pspMapper->getStockGames();
    std::map<std::string, pspConfigGameDef>::iterator it;
    for ( it = pspGames.begin(); it != pspGames.end(); it++ )
    {
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

ModePspStockfix::ModePspStockfix(std::string &targetDir) : targetDir(targetDir) {

}

int ModePspStockfix::patchControlFolder(std::string source, std::string target, pspConfigGameDef gameDef) {
    Fs::makeDirectory(target + "PSP");
    Fs::makeDirectory(target + "PSP/SYSTEM");
    Fs::copy(source + "controls" + std::to_string(gameDef.controlType) +".ini", target + "PSP/SYSTEM/controls.ini");
    Fs::copy(source + "ppsspp" +std::to_string(gameDef.ppssppSettings)+ ".ini", target + "PSP/SYSTEM/ppsspp.ini");
    return 0;
}
