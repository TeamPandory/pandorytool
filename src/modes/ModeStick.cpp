#include <iostream>
#include "../Fs.h"
#include "ModeStick.h"
#include "../StickExtractor.h"
#include "../types.h"
#include "../StickDownloader.h"
#include "../definitions/Sticks.h"

int ModeStick::main() {
    Sticks sticks;
    stick selectedStick = sticks.getStickByName(stickType);

    if (!selectedStick.stickName.empty()) {
        return makeStick(selectedStick);
    }

    std::cout << "The specified stick `" << stickType << "` is not available." << std::endl;
    return 1;
}

int ModeStick::makeStick(stick stickData) {
    if (!Fs::exists(targetDir)) {
        std::cout << "Could not create stick. " << targetDir << " does not exist." << std::endl;
        return 1;
    }
    std::cout << "Creating " << stickData.stickName << "-stick at " << targetDir << std::endl;

    StickDownloader sdl;
    std::string tar = sdl.download(stickData);
    StickExtractor stickExtractor;
    stickExtractor.exractToFolder(stickData, tar, targetDir);
    std::cout << stickData.stickDescription << std::endl;
    return 0;
}
ModeStick::ModeStick(std::string &stickType, std::string &targetDir) : stickType(stickType), targetDir(targetDir) {}

