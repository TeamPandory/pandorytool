#include <iostream>
#include "ModePspStockfix.h"
#include "../Fs.h"

int ModePspStockfix::main() {
    std::cout << "Attempting to fix stock PSP game controls..." << std::endl;

    std::string path = targetDir + "/games/data/family/PSP0000/";
    if (!Fs::exists(path)) {
        std::cout << path << " could not be found " << std::endl;
        std::cout << "Please install the PSP0000 game using `pandory add` in order to use pspstockfix." << std::endl;
        return 1;
    }
    Fs::makeDirectory(path + "PSP");
    Fs::makeDirectory(path + "PSP/SYSTEM");
    Fs::copy(path + "controls0.ini", path + "PSP/SYSTEM/controls.ini");
    Fs::copy(path + "ppsspp2.ini", path + "PSP/SYSTEM/ppsspp.ini");

    return 0;
}

ModePspStockfix::ModePspStockfix(std::string &targetDir) : targetDir(targetDir) {

}
