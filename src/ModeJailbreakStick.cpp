
#include <iostream>
#include "ModeJailbreakStick.h"

int ModeJailbreakStick::getChoice() {
    int jailbreakType = 0;
    std::cout << std::endl;
    std::cout << "Please choose the console you wish to jailbreak:" << std::endl;
    std::cout << "[1] - Pandora Games 3D (2448/4018 Games, GB3000 board up to firmware 20200217)" << std::endl;
    std::cout << "    - Pandora 3D Saga (2650 Games, PSA-S812-001 board, with or without NAND)" << std::endl;
    std::cout << "    - 3D Pandora Saga Wifi TV Game Box 3000" << std::endl;
    std::cout << "    - ..other \"Moorechip\" Pandora clones (3D Saga/X/Key7 - PSA-S812/GB3000 boards)" << std::endl;
    std::cout << "[2] - Pandora Games 3D+ (4018 Games, GB3000 board with firmware 20200704 onwards)" << std::endl;
    std::cout << "[3] - Pandora Key 7 (Red/Green motherboard) Requires a Micro-SD card. Will NOT work on USB stick!" << std::endl << std::endl;
    std::cout << "Enter a number, followed by [ENTER]: ";
    jailbreakType = getchar();

    if (jailbreakType == 49) { //3d
        return 1;
    } else if (jailbreakType == 50) { //3dplus
        return 2;
    } else if (jailbreakType == 51) { //7
        return 3;
    }
    return -1;
}
