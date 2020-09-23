#include <iostream>
#include "../Fs.h"
#include "ModeStick.h"
#include "../StickExtractor.h"
#include "../StickDownloader.h"
#include <fstream>

#include <chrono>
#include <thread>


int ModeStick::main() {
    downloadDefinition selectedStick = sticks.getStickByName(stickType);

    if (!selectedStick.name.empty()) {
        return makeStick(selectedStick);
    }
    std::cout << "The specified stick `" << stickType << "` is not available." << std::endl;
    return 1;
}

int ModeStick::makeStick(const downloadDefinition &stickData) {
    if (!Fs::exists(targetDir)) {
        std::cout << "Could not create stick. " << targetDir << " does not exist." << std::endl;
        return 1;
    }
    std::cout << "Creating " << stickData.name << "-stick at " << targetDir << std::endl;

    downloadDefinition stickToDownload;

    if (stickData.name == "jailbreak") {
        int choice = modeJailbreakStick.getChoice();
        if (choice == 1) {
            stickToDownload = sticks.getStickByName("jailbreak3D");
        } else if (choice == 2) {
            stickToDownload = sticks.getStickByName("jailbreak3DPlus");
        }else if (choice == 3) {
            stickToDownload = sticks.getStickByName("jailbreak7");
        } else {
            exit(0);
        }
    } else {
        stickToDownload = stickData;
    }

    StickDownloader sdl;
    std::string tar = sdl.download(stickToDownload);
    StickExtractor stickExtractor;
    stickExtractor.exractToFolder(stickToDownload, tar, targetDir);
    std::cout << stickToDownload.description << std::endl;

    if (stickToDownload.name == "jailbreak3D" || stickToDownload.name == "jailbreak3DPlus"  || stickToDownload.name == "jailbreak7") {
        int x = 0;
        std::ofstream defFile, resFile;
        std::string suffix;
        defFile.open(targetDir + "/OTA/pandory/meta.bin");
        resFile.open(targetDir + "/OTA/pandory/res.bin");
        std::string defContent = "/dev/block/system";
        if (editionCheck.isUltimate()) {
            defContent = "/dev/block/d";
            defContent += "ata";
        }

        if (editionCheck.isShareware() && stickToDownload.name == "jailbreak3D") {
            std::cout << std::endl;
            std::cout << "Did you know that the Pandory Jailbreak includes an additional automatic aspect-ratio switching" <<std::endl;
            std::cout << "feature for users who have supported the project by buying us a coffee?" << std::endl;
            std::cout << "If you are interested in using this feature, please visit https://www.buymeacoffee.com/CKZbiXa " << std::endl;
            std::cout << "and we will send you a copy of the ultimate version. Thanks!" << std::endl;
            suffix = "s";
        }

        if (editionCheck.isUltimate() || stickToDownload.name == "jailbreak7") {
            std::cout << std::endl;
            std::cout << "The Pandory Jailbreak includes automatic aspect-ratio switching." << std::endl;
            std::cout << "If you use a 4:3 VGA monitor, or wish to disable aspect-ratio switching, " << std::endl;
            std::cout << "please press V now or press any other key to continue." << std::endl;
            suffix = "u";
            while ((x = getchar()) != '\n' && x != EOF);
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
    std::cout << std::endl << "Jailbreak stick complete. Have fun!" << std::endl;
    return 0;
}
ModeStick::ModeStick(std::string &stickType, std::string &targetDir) : stickType(stickType), targetDir(targetDir) {}

