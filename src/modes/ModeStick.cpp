#include <iostream>
#include "../Fs.h"
#include "ModeStick.h"
#include "../StickExtractor.h"
#include "../types.h"
#include "../StickDownloader.h"

int ModeStick::main() {
    if (stickType == "jailbreak") {
        return jailbreak();
    }
    if (stickType == "backup") {
        return backup();
    }
    std::cout << "The specified stick `" << stickType << "` is not available." << std::endl;
    return 1;
}

ModeStick::ModeStick(std::string &stickType, std::string &targetDir) : stickType(stickType), targetDir(targetDir) {}

int ModeStick::jailbreak() {
    if (!Fs::exists(targetDir)) {
        std::cout << "Could not create stick. " << targetDir << " does not exist." << std::endl;
        return 1;
    }
    stick jailbreakStick = {
            "jailbreak",
            "https://github.com/emuchicken/pandorytool/archive/stick-jailbreak.tar.gz"
    };
    std::cout << "Creating Jailbreak Stick at " << targetDir << std::endl;
    StickExtractor stickExtractor;
    stickExtractor.exractToFolder(jailbreakStick.stickName, stickType, targetDir);
    std::cout << "This USB will patch your system to run `pandory.sh` off the USB drive when inserted." << std::endl
              << "`pandory.sh` is a bash-shellscript. By default it starts the android launcher, but can" << std::endl
              << "be configured to do anything you like. This means you can use this stick as a base to make your " << std::endl
              << "own sticks." << std::endl << std::endl
              << "After a successful jailbreak, the stick is reconfigured to act as a dedicated `Launch Android`-Stick." << std::endl;

    std::cout << "Insert this USB while booted. If the update gets stuck on a black screen with chinese text, " << std::endl
              << "reboot the machine and try again." << std::endl;
    return 0;
}

int ModeStick::backup() {
    if (!Fs::exists(targetDir)) {
        std::cout << "Could not create stick. " << targetDir << " does not exist." << std::endl;
        return 1;
    }
    std::cout << "Creating Backup-To-USB Stick at " << targetDir << std::endl;

    stick backupStick = {
            "backup",
            "https://github.com/emuchicken/pandorytool/archive/stick-backup.tar.gz"
    };
    StickDownloader sdl;
    std::string tar = sdl.download(backupStick);

    StickExtractor stickExtractor;
    stickExtractor.exractToFolder(backupStick.stickName, tar, targetDir);
    std::cout << "This stick will backup your machine system/data-partitions to your USB drive." << std::endl;
    std::cout << std::endl;
    std::cout << "Insert this USB while booted. If the update gets stuck on a black screen with chinese text, " << std::endl
              << "reboot the machine and try again." << std::endl;
    return 0;
}
