#include "McGamesAbstract.h"

void McGamesAbstract::setEmulatorId(const std::string &emulatorName) {
    McGamesAbstract::emulatorId = emulatorName;
}

void McGamesAbstract::setEmulatorLoad(const std::string &emulatorLoad) {
    McGamesAbstract::emulatorLoad = emulatorLoad;
}

void McGamesAbstract::setRomShortId(const std::string &romFileName) {
    McGamesAbstract::romShortId = romFileName;
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

void McGamesAbstract::setGenre(int genre) {
    McGamesAbstract::genre = genre;
}

void McGamesAbstract::setRomDeveloper(const std::string &romDeveloper) {
    McGamesAbstract::romDeveloper = romDeveloper;
}

void McGamesAbstract::setRomPath(const std::string &romPath) {
    McGamesAbstract::romDirectory = romPath;
}

void McGamesAbstract::setRomTitle(const std::string &romTitle) {
    McGamesAbstract::romFullName = romTitle;
}

void McGamesAbstract::setPlayers(const std::string &players) {
    McGamesAbstract::players = players;
}

void McGamesAbstract::setSaveState(bool saveState) {
    McGamesAbstract::saveState = saveState;
}

void McGamesAbstract::setRomFileName(const std::string &romFileName) {
    McGamesAbstract::romFileName = romFileName;

}
