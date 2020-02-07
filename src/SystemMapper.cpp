#include "SystemMapper.h"

std::string SystemMapper::convertDirectoryNameToSystemName(std::string dir) {
    if (dir == "dreamcast") return "DC";
    if (dir == "gba") return "GBA";
    if (dir == "gbc") return "GBC";
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

    //...MAME...
    //...
    return "";
}
