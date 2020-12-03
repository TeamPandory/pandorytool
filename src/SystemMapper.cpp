#include <string>
#include <algorithm>
#include "SystemMapper.h"
#include "termcolor/termcolor.hpp"

SystemDefinition SystemMapper::getSystemDefinition(const std::string &dir) {
    if (dir == "fba") return SystemDefinition(1,2, "FBA", "", true, false);
    if (dir == "mame37") return SystemDefinition(2,0, "MAME37", "", true, false);
    if (dir == "mame139") return SystemDefinition(3,0, "MAME139", "", true, false);
    if (dir == "mame78") return SystemDefinition(4,0, "MAME139", "", true, false);
    if (dir == "psp") return SystemDefinition(6,3, "PSP", "", true, true);
    if (dir == "playstation") return SystemDefinition(7,0, "PS", "", true, true);
    if (dir == "n64") return SystemDefinition(8,3, "N64", "", false, true);
    if (dir == "nes") return SystemDefinition(11,3, "NES", "", true, true);
    if (dir == "snes") return SystemDefinition(12,0, "SNES", "", true, true);
    if (dir == "gba") return SystemDefinition(13,0, "GBA", "", true, true);
    if (dir == "gb") return SystemDefinition(14,0, "GB", "", true, true);
    if (dir == "gbc") SystemDefinition(14,0, "GBC", "", true, true);
    if (dir == "32x") return SystemDefinition(15,3, "32X", "", true, true);
    if (dir == "gamegear") SystemDefinition(15,0, "GG", "", true, true);
    if (dir == "mastersystem") SystemDefinition(15,0, "MS", "", true, true);
    if (dir == "megadrive") SystemDefinition(15,3, "MD", "", true, true);
    if (dir == "wswan") return SystemDefinition(16,0, "WSWAN", "", true, false);
    if (dir == "pcengine") return SystemDefinition(17,0, "PCE", "", true, true);
    if (dir == "dreamcast") return SystemDefinition(18,3, "DC", "", true, true);
    if (dir == "mame19") return SystemDefinition(19,0, "MAME19", "", true, false);
    return SystemDefinition();
}

std::string SystemMapper::convertDirectoryNameToSystemName(std::string dir) {
    if (dir == "gb") return "GB";
    if (dir == "gbc") return "GBC";
    if (dir == "gamegear") return "GG";
    if (dir == "mastersystem") return "MS";
    if (dir == "megadrive") return "MD";
    if (dir == "n64") return "N64";
    if (dir == "playstation") return "PS";
    if (dir == "psp") return "PSP";
    if (dir == "snes") return "SNES";
    if (dir == "nes") return "NES";
    if (dir == "pcengine") return "PCE";
    if (dir == "fba") return "FBA";
    if (dir == "mame19") return "MAME19";
    if (dir == "mame37") return "MAME37";
    if (dir == "mame139") return "MAME139";
    if (dir == "mame78") return "MAME78";
    if (dir == "wswan") return "WSWAN";
    //...MAME...
    //...
    return "";
}

void SystemMapper::setConsoleColourBySystem(const std::string &dir) {
    if (dir == "gba") std::cout << termcolor::red;
    if (dir == "gb") std::cout << termcolor::red;
    if (dir == "gbc") std::cout << termcolor::red;
    if (dir == "megadrive") std::cout << termcolor::blue;
    if (dir == "mastersystem") std::cout << termcolor::blue;
    if (dir == "gamegear") std::cout << termcolor::blue;
    if (dir == "n64") std::cout << termcolor::red;
    if (dir == "playstation") std::cout << termcolor::green;
    if (dir == "psp") std::cout << termcolor::green;
    if (dir == "snes") std::cout << termcolor::red;
    if (dir == "nes") std::cout << termcolor::red;
    if (dir == "pcengine") std::cout << termcolor::yellow;
    if (dir == "fba") std::cout << termcolor::cyan;
    if (dir == "mame19") std::cout << termcolor::magenta;
    if (dir == "mame37") std::cout << termcolor::magenta;
    if (dir == "mame139") std::cout << termcolor::magenta;
    if (dir == "mame78") std::cout << termcolor::magenta;
    if (dir == "wswan") std::cout << termcolor::yellow;
}

int SystemMapper::getSystemSaveState(const std::string &dir) {
    // if (dir == "fba") return false; - My bad, I think this emulator actually saves :o
    if (dir == "n64") return false;
    //if (dir == "mame19") return false;
    //if (dir == "mame37") return false;
    //if (dir == "mame139") return false;
    //if (dir == "mame78") return false;
    return true;
}

bool SystemMapper::getSystemRenameFlag(const std::string &dir) {
    if (dir == "fba") return false;
    if (dir == "mame19") return false;
    if (dir == "mame37") return false;
    if (dir == "mame139") return false;
    if (dir == "mame78") return false;
    return true;
}

int SystemMapper::getGenre(const std::string &genreString) {
    std::string genre = genreString;
    std::transform(genre.begin(), genre.end(), genre.begin(), ::tolower);

    if (genre.find("fight") != std::string::npos
       || genre.find("beat") != std::string::npos
       ) {
        return 1;
    } else if (genre.find("action") != std::string::npos
               || genre.find("platform") != std::string::npos
               || genre.find("adventure") != std::string::npos
               || genre.find("role") != std::string::npos
               || genre.find("pinball") != std::string::npos
               || genre.find("simulation") != std::string::npos
              ) {
        return 2;
    } else if (genre.find("shoot") != std::string::npos) {
        return 3;
    } else if (genre.find("sport") != std::string::npos) {
        return 4;
    } else if (genre.find("puzzle") != std::string::npos
               || genre.find("strategy") != std::string::npos) {
        return 5;
    } else if (genre.find("race") != std::string::npos
               || genre.find("driving") != std::string::npos) {
        return 6;
    }
    return 0;
}
