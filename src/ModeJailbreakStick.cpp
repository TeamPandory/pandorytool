
#include <iostream>
#include "ModeJailbreakStick.h"

int ModeJailbreakStick::getChoice() {
    int jailbreakType = 0;
    std::cout << std::endl;
    std::cout << "Please choose the console you wish to jailbreak:" << std::endl;
    std::cout << "[1] - Pandora Games 3D (Supports up to firmware 20200217. Requires a USB stick)" << std::endl;
    std::cout << "[2] - Pandora Key 7 (Requires a Micro-SD card. Will NOT work on USB stick)" << std::endl << std::endl;
    std::cout << "Enter a number, followed by [ENTER]: ";
    jailbreakType = getchar();

    if (jailbreakType == 49) { //3d
        return 1;
    } else if (jailbreakType == 50) { //7
        return 2;
    }
    return -1;
}
