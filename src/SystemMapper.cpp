#include "SystemMapper.h"
#include "termcolor/termcolor.hpp"

std::string SystemMapper::convertDirectoryNameToSystemName(std::string dir) {
    if (dir == "dreamcast") return "DC";
    if (dir == "gba") return "GBA";
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

void SystemMapper::setConsoleColourBySystem(const std::string& dir) {
	if (dir == "dreamcast") std::cout << termcolor::blue;
	if (dir == "gba") std::cout << termcolor::red;
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

int SystemMapper::getSystemSaveState(const std::string& dir) {
   // if (dir == "fba") return false; - My bad, I think this emulator actually saves :o
    if (dir == "n64") return false;
    //if (dir == "mame19") return false;
    //if (dir == "mame37") return false;
    //if (dir == "mame139") return false;
    //if (dir == "mame78") return false;
    return true;
}

bool SystemMapper::getSystemRenameFlag(const std::string& dir) {
    if (dir == "fba") return false;
    if (dir == "mame19") return false;
    if (dir == "mame37") return false;
    if (dir == "mame139") return false;
    if (dir == "mame78") return false;
    return true;
}
