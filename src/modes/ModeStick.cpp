#include <iostream>
#include "../Fs.h"
#include "ModeStick.h"
#include "../StickExtractor.h"
#include "../types.h"
#include "../StickDownloader.h"
#include "../definitions/Sticks.h"

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
/*
    StickDownloader sdl;
    std::string tar = sdl.download(stickData);
    StickExtractor stickExtractor;
    stickExtractor.exractToFolder(stickData, tar, targetDir);
    std::cout << stickData.description << std::endl;*/

    if (stickData.name == "jailbreak") {
        std::string dat = "00000000";
        if (editionCheck.isShareware()) {
            std::cout << "Did you that the Pandory Jailbreak includes automatic aspect-ratio switching for users who" << std::endl;
            std::cout << "have bought us a coffee to support the project." << std::endl;
            std::cout << "If you are interested in using this feature, please visit" << std::endl;
            std::cout << "https://www.buymeacoffee.com/CKZbiXa and we will send you a copy of the ultimate version. Thanks!";
        }

        if (editionCheck.isUltimate()) {
            std::cout << "The Pandory Jailbreak includes automatic aspect-ratio switching." << std::endl;
            std::cout << "If you use a 4:3 VGA monitor, or wish to disable aspect-ratio switching, " << std::endl;
            std::cout << "please press V now or press any other key to continue." << std::endl;
            int x = getchar();
            dat = "81920000";
            if (x == 86 || x == 118) {
                dat = "40960000";
            }
            std::cout << x << std::endl;

        }
    }
    return 0;
}
ModeStick::ModeStick(std::string &stickType, std::string &targetDir) : stickType(stickType), targetDir(targetDir) {}

