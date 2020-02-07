#include "McGamesAbstract.h"

void McGamesAbstract::setEmulatorName(const std::string &emulatorName) {
    McGamesAbstract::emulatorName = emulatorName;
}

void McGamesAbstract::setRomName(const std::string &romName) {
    McGamesAbstract::romName = romName;
}

void McGamesAbstract::setRomDescription(const std::string &romDescription) {
    McGamesAbstract::romDescription = romDescription;
}

void McGamesAbstract::setLanguage(const std::string &language) {
    McGamesAbstract::language = language;
}

void McGamesAbstract::setYear(int year) {
    McGamesAbstract::year = year;
}

void McGamesAbstract::setRomDeveloper(const std::string &romDeveloper) {
    McGamesAbstract::romDeveloper = romDeveloper;
}

void McGamesAbstract::setRomPath(const std::string &romPath) {
    McGamesAbstract::romPath = romPath;
}
