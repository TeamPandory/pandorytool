#include "McGamesAbstract.h"

void McGamesAbstract::setEmulatorId(const std::string& emulatorName)
{
    McGamesAbstract::emulatorId = emulatorName;
}

void McGamesAbstract::setEmulatorLoad(const std::string& emulatorLoad)
{
    McGamesAbstract::emulatorLoad = emulatorLoad;
}

void McGamesAbstract::setRomShortId(const std::string& romFileName)
{
    McGamesAbstract::romShortId = romFileName;
}

void McGamesAbstract::setRomDescription(const std::string& romDescription)
{
    McGamesAbstract::romDescription = romDescription;
}

void McGamesAbstract::setLanguage(const std::string& language)
{
    McGamesAbstract::language = language;
}

void McGamesAbstract::setYear(int year)
{
    McGamesAbstract::year = year;
}

void McGamesAbstract::setGenre(int genre)
{
    McGamesAbstract::genre = genre;
}

void McGamesAbstract::setRomDeveloper(const std::string& developerName)
{
    McGamesAbstract::romDeveloper = developerName;
}

void McGamesAbstract::setRomTitle(const std::string& title)
{
    McGamesAbstract::romTitle = title;
}

void McGamesAbstract::setPlayers(const std::string& numberOfPlayers)
{
    McGamesAbstract::players = numberOfPlayers;
}

void McGamesAbstract::setSaveState(bool saveStateStatus)
{
    McGamesAbstract::saveState = saveStateStatus;
}

void McGamesAbstract::setRomFileName(const std::string& filename)
{
    McGamesAbstract::romFileName = filename;
}

void McGamesAbstract::addAdditionalRom(std::string& additionalRomNames)
{
    McGamesAbstract::additionalRomName = additionalRomNames;
}

void McGamesAbstract::setFileHash(const std::string& fileCrc)
{
    McGamesAbstract::fileHash = fileCrc;
}

std::string McGamesAbstract::getFileHash()
{
    return McGamesAbstract::fileHash;
}

std::string McGamesAbstract::getRomTitle()
{
    return romTitle;
}

std::string McGamesAbstract::getConsole()
{
    return McGamesAbstract::console;
}

void McGamesAbstract::setConsole(const std::string& consoleName)
{
    McGamesAbstract::console = consoleName;
}

int McGamesAbstract::getYear() const
{
    return year;
}

void McGamesAbstract::setRomTitleSuffix(const std::string& titleSuffix)
{
    McGamesAbstract::romTitleSuffix = titleSuffix;
}

const std::string& McGamesAbstract::getRomTitleSuffix() const
{
    return romTitleSuffix;
}
