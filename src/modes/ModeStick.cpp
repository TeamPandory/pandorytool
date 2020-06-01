#include <iostream>
#include "../Fs.h"
#include "ModeStick.h"
#include "../StickExtractor.h"
#include "../types.h"
#include "../StickDownloader.h"
#include "../definitions/Sticks.h"
#include <fstream>

#include <chrono>
#include <thread>


int ModeStick::main() {
    Sticks sticks;
    downloadDefinition selectedStick = sticks.getStickByName(stickType);

    if (!selectedStick.name.empty()) {
        return makeStick(selectedStick);
    }

    std::cout << "The specified stick `" << stickType << "` is not available." << std::endl;
    return 1;
}

int ModeStick::makeStick(downloadDefinition stickData) {
    if (!Fs::exists(targetDir)) {
        std::cout << "Could not create stick. " << targetDir << " does not exist." << std::endl;
        return 1;
    }
    std::cout << "Creating " << stickData.name << "-stick at " << targetDir << std::endl;

    StickDownloader sdl;
    std::string tar = sdl.download(stickData);
    StickExtractor stickExtractor;
    stickExtractor.exractToFolder(stickData, tar, targetDir);
    std::cout << stickData.description << std::endl;

    if (stickData.name == "jailbreak") {
        int x = 0;
        std::ofstream defFile, resFile;
        std::string suffix;
        defFile.open(targetDir + "/pandory/meta.bin");
        resFile.open(targetDir + "/pandory/res.bin");
        std::string defContent = "/dev/block/system";
        if (editionCheck.isUltimate()) {
            defContent = "/dev/block/d";
            defContent += "ata";
        }

        if (editionCheck.isShareware()) {
            std::cout << std::endl;
            std::cout << "Did you that the Pandory Jailbreak includes automatic aspect-ratio switching for users who"
                      << std::endl;
            std::cout << "have bought us a coffee to support the project." << std::endl;
            std::cout << "If you are interested in using this feature, please visit" << std::endl;
            std::cout
                    << "https://www.buymeacoffee.com/CKZbiXa and we will send you a copy of the ultimate version. Thanks!";
            suffix = "s";
        }

        if (editionCheck.isUltimate()) {
            std::cout << std::endl;
            std::cout << "The Pandory Jailbreak includes automatic aspect-ratio switching." << std::endl;
            std::cout << "If you use a 4:3 VGA monitor, or wish to disable aspect-ratio switching, " << std::endl;
            std::cout << "please press V now or press any other key to continue." << std::endl;
            suffix = "u";
            x = getchar();
        }

        std::string dat = "16:9";
        if (x == 86 || x == 118) {
            dat = "4:3";
        }

        defFile << defContent;
        defFile.close();
        resFile << dat << suffix;
        resFile.close();
    }
    return 0;
}
ModeStick::ModeStick(std::string &stickType, std::string &targetDir) : stickType(stickType), targetDir(targetDir) {}

