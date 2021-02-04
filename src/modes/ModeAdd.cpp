#include <iostream>
#include <filesystem>
#include <algorithm>
#include <tinyxml2.h>
#include <regex>
#include <thread>
#include "ModeAdd.h"
#include "../termcolor/termcolor.hpp"
#include "../EditionCheck.h"

std::string ModeAdd::pad(std::string string, const size_t size, const char character = ' ') {
    if (size > string.size()) {
        string.insert(0, size - string.size(), character);
    }
    return string;
}

bool ModeAdd::validate() {
    if (!Fs::exists(sourceDir)) {
        std::cout << sourceDir << " does not exist " << std::endl;
        return false;
    }
    if (!Fs::exists(targetDir)) {
        std::cout << targetDir << " does not exist " << std::endl;
        return false;
    }
    return true;
}

ModeAdd::ModeAdd(std::string &sourceDir, std::string &targetDir) : sourceDir(sourceDir), targetDir(targetDir) {
}

void ModeAdd::getScreenScraperDetails() {
    std::cout << "To add games, it is advisable to have a free ScreenScraper.fr account." << std::endl;
    std::cout << "Register one here: https://screenscraper.fr/membreinscription.php" << std::endl;
    std::cout << "If you want to skip this step, just press enter twice." << std::endl << std::endl;

    std::cout << "Please enter your screenscraper.fr details: " << std::endl;
    std::cout << "Username: ";
    getline(std::cin, screenscrapeUsername);
    scrapeService.setUsername(screenscrapeUsername);
    std::cout << "Password: ";
    //console.disableEcho();
    getline(std::cin, screenscrapePassword);
    scrapeService.setPassword(screenscrapeUsername);
    //console.enableEcho();
}

// 1. Add games (MCGames)
int ModeAdd::main() {
    if (!validate()) {
        return 1;
    }
    getScreenScraperDetails();
    std::cout
            << "-----------------------------------------------------------------------------------------------------"
            << std::endl;
    if (!Fs::exists("scrapes")) {
        Fs::makeDirectory("scrapes");
    }
    createTargetDirectory();
    resetInstallFile();
    resetMcGamesFolder();

    parseSourceDirectory();
    return 0;
}

void ModeAdd::parseSourceDirectory() {
    openInstallFileHandle();
    for (const auto &entry : std::filesystem::directory_iterator(this->sourceDir)) {
        std::string filePath = entry.path().string();
        std::string basename = Fs::basename(filePath);
        parseRomFolder(filePath);
        std::cout
                << "-----------------------------------------------------------------------------------------------------"
                << std::endl;
    }
    closeInstallFileHandle();
}

std::string ModeAdd::getRomSuffix(const std::string &romFilename) {
    std::string suffix;
    std::string countries;
    std::string flags;
    std::string date;
    // countries
    if (std::regex_search(romFilename, std::regex("\\(.*JAPAN.*\\)", std::regex::icase))) countries.append("J");
    if (std::regex_search(romFilename, std::regex("\\(.*USA.*\\)", std::regex::icase))) countries.append("U");
    if (std::regex_search(romFilename, std::regex("\\(.*EUROPE.*\\)", std::regex::icase))) countries.append("E");
    if (std::regex_search(romFilename, std::regex("\\(.*BRASIL.*\\)", std::regex::icase))) countries.append("B");
    if (std::regex_search(romFilename, std::regex("\\(.*KOREA.*\\)", std::regex::icase))) countries.append("K");
    if (std::regex_search(romFilename, std::regex("\\(.*CHINA.*\\)", std::regex::icase))) countries.append("C");
    // flags
    if (std::regex_search(romFilename, std::regex("\\(.*DEMO.*\\)", std::regex::icase))) flags.append("D");
    if (std::regex_search(romFilename, std::regex("\\(.*BETA.*\\)", std::regex::icase))) flags.append("B");
    if (std::regex_search(romFilename, std::regex("\\(.*HACK.*\\)", std::regex::icase))) flags.append("H");
    if (std::regex_search(romFilename, std::regex("\\(.*PROTO.*\\)", std::regex::icase))) flags.append("P");
    if (std::regex_search(romFilename, std::regex("\\(.*UNL.*\\)", std::regex::icase))) flags.append("U");

    std::regex re("(\\d{4}-\\d{2}-\\d{2})");
    std::smatch match;
    if (regex_search(romFilename, match, re)) {
        date.append(match.str(0));
    }

    if (!countries.empty()) {
        suffix = " (" + countries + ")";
    }
    if (!flags.empty()) {
        suffix.append(" [" + flags + "]");
    }
    if (!date.empty()) {
        suffix.append(" [" + date + "]");
    }
    return suffix;
}

void ModeAdd::parseRomFolder(const std::string &romFolder) {
    int i = 1;
    std::string system = Fs::basename(romFolder);
    std::string shortSystemName = systemMapper.convertDirectoryNameToSystemName(system);
    if (shortSystemName.empty()) {
        std::cout << "Skipping unknown system: " << system << std::endl;
        return;
    }
    std::cout << "Processing: " << system << std::endl;

    std::vector<std::string> filenames;
    for (const auto &entry : std::filesystem::directory_iterator(romFolder)) {
        if (!entry.is_directory()) {
            filenames.push_back(entry.path().string());
        }
    }
    std::sort(filenames.begin(), filenames.end());

    for (const auto &filePath : filenames) {
        if (checkSharewareLimit(i)) break;
        std::cout << Fs::basename(filePath);
        scrapeService.setFilename(filePath);
        int result = scrapeService.scrapeRom();

        if (result == 0) {
            McGamesXML mcGamesXml = scrapeService.getMcGamesXML();
            McGamesTXT mcGamesTxt = scrapeService.getMcGamesTXT();
            std::string md5 = hash.md5_file(filePath);
            mcGamesXml.setFileHash(md5.substr(0,8));

            if (!shortSystemName.empty()) {
                std::string targetRomName;
                targetRomName = calculateRomName(i, system, filePath, mcGamesXml, shortSystemName, targetRomName);

                std::string targetFilePath = targetRomName + Fs::extension(filePath);

                std::string baseFilename = Fs::basename(filePath);
                std::string titleSuffix = getRomSuffix(baseFilename);
                std::string romTitle = mcGamesXml.getRomTitle();
                if (!titleSuffix.empty()) {
                    romTitle.append(titleSuffix);
                    mcGamesXml.setRomTitle(romTitle);
                } else {
                    std::string scrapeSuffix = mcGamesXml.getRomTitleSuffix();
                    if (!scrapeSuffix.empty()) {
                        romTitle.append(" (" + scrapeSuffix + ")");
                        mcGamesXml.setRomTitle(romTitle);
                    }
                }
                showRomIdentification(system, mcGamesXml);

                mcGamesXml.setRomShortId(targetRomName);
                mcGamesTxt.setRomShortId(targetRomName);
                mcGamesXml.setRomFileName(Fs::basename(targetFilePath));
                mcGamesTxt.setRomFileName(Fs::basename(targetFilePath));


                installFile << targetRomName << std::endl;
                std::string targetRomDir = targetDir + "/mcgames/" + targetRomName;

                // copy controls
                // mame controls
                std::string additionalRom;
                std::string controlsPath = "./controls/" + system + "/" + targetRomName + ".cfg";
                bool deleteControls = false;
                std::string fbaIniPath = "./controls/fba/fba.ini";
                std::string romIniPath;
                if (system == "fba") {
                    romIniPath = "./controls/fba/" + targetRomName + ".ini";
                    Fs::copy(fbaIniPath, romIniPath);
                    controlsPath = romIniPath;
                    deleteControls = true;
                }
                if (Fs::exists(controlsPath)) {
                    additionalRom = Fs::basename(controlsPath);
                    mcGamesXml.addAdditionalRom(additionalRom);
                    copyRomToDestination(controlsPath, targetRomDir, false);
                    if (deleteControls) {
                        Fs::remove(romIniPath);
                    }
                }
                // end copy controls

                try {
                    bool rename = systemMapper.getSystemRenameFlag(system);
                    copyRomToDestination(filePath, targetRomDir, rename);

                    std::string targetBase;
                    targetBase.append(targetRomDir);
                    targetBase.append("/");
                    targetBase.append(targetRomName);

                    std::string targetXml;
                    targetXml.append(targetBase);
                    targetXml.append(".xml");
                    mcGamesXml.generate(targetXml);

                    std::string targetTxt;
                    targetTxt.append(targetBase);
                    targetTxt.append(".txt");
                    mcGamesTxt.generate(targetTxt);
                } catch (...) {
                    std::cout << " ## ERROR COPYING: " << filePath << " TO " << targetRomName << "...skipping"
                              << std::endl;
                    continue;
                }

                // copy video
                std::string videoPath;
                ScreenScraperXML *scrapedXml = scrapeService.getScreenScraperXml();
                videoPath.append("scrapes/" + std::to_string(scrapedXml->getId()));
                videoPath.append("/" + std::to_string(scrapedXml->getId()) + ".mp4");
                if (Fs::exists(videoPath) && !videoPath.empty()) {
                    copyRomVideoToDestination(videoPath, targetRomDir);
                }
                i++;
            }
        } else {
            std::cout << " - Problem scraping rom. Waiting 10 seconds..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        }
    }
}

std::string &
ModeAdd::calculateRomName(int i, const std::string &system, const std::string &filePath, McGamesXML &mcGamesXml,
                          const std::string &shortSystemName, std::string &targetRomName) {
    targetRomName = shortSystemName + "_" + pad(std::to_string(i), 5, '0');
    EditionCheck ed;
    if (ed.isUltimate()) {
        std::string hash = "_" + mcGamesXml.getFileHash();
        if (!hash.empty()) {
            targetRomName = shortSystemName + hash;
        }
    }
    if (!systemMapper.getSystemRenameFlag(system)) {
        targetRomName = Fs::stem(filePath);
    }
    return targetRomName;
}

void ModeAdd::showRomIdentification(const std::string &system, McGamesXML &mcGamesXml) {
    systemMapper.setConsoleColourBySystem(system);
    std::cout << " - Identified as: ";
    std::string systemName = mcGamesXml.getConsole();
    std::cout << systemName;
    std::cout << " - " << mcGamesXml.getRomTitle() << std::endl;
    std::cout << termcolor::reset;
}

bool ModeAdd::checkSharewareLimit(int i) {
#ifndef NO_SHAREWARE_LIMIT
    int limit = 20;
        if (i > limit) {
            std::cout << std::endl;
            std::cout << "pandorytool is freeware and is the product of many hours of blood, sweat and tears. " << std::endl;
            std::cout << "This version is limited to " << limit << " roms." << std::endl;
            std::cout << "If you wish to transfer more, you can compile the source ";
            std::cout << "code yourself, or consider supporting us by grabbing us a coffee at" << std::endl;
            std::cout << "https://www.buymeacoffee.com/CKZbiXa and we will send you a copy of the unlimited version. Thanks!";
            std::cout << std::endl;
            return true;
        }
#endif
    return false;
}

void ModeAdd::openInstallFileHandle() {
    installFile.open(getInstallFilePath().c_str());
}

void ModeAdd::closeInstallFileHandle() {
    installFile.close();
}


// Checks subfolders within “source rom folder”.
// Copies both rom file
// – to usbdevice:\mcgames\DC0001 (if dreamcast game) – check “ARSENAME” below for naming convention.
// Both DC0001.cdi should be within the mcgames/DC0001 folder.
void ModeAdd::copyRomToDestination(const std::string &rom, const std::string &destination, bool rename) {
    std::string basename;
    std::string extension;
    if (rename) {
        basename = Fs::basename(destination);
        extension = Fs::extension(rom);
    } else {
        basename = Fs::basename(rom);
        extension = "";
    }
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    Fs::makeDirectory(destination);
    Fs::copy(rom, destination + "/" + basename + extension);
}

// – (and if available, mp4 file (from romsubfolder/media/videos))
// DC0001.mp4 should be within the mcgames/DC0001 folder.
void ModeAdd::copyRomVideoToDestination(const std::string &absoluteVideoPath, const std::string &destination) {
    std::string basename = Fs::basename(destination);
    std::string extension = Fs::extension(absoluteVideoPath);
    Fs::makeDirectory(destination);
    Fs::copy(absoluteVideoPath, destination + "/" + basename + extension);
}

// remove install.txt file if exists, open clear file
void ModeAdd::resetInstallFile() {
    std::string mcInstall = getInstallFilePath();
    FILE *foo;
    foo = fopen(mcInstall.c_str(), "w");
    fclose(foo);
}

void ModeAdd::resetMcGamesFolder() {
    std::string mgGamesFolder = getMcGamesFolder();
    Fs::remove(getMcGamesFolder());
    Fs::makeDirectory(getMcGamesFolder());
}

std::string ModeAdd::getInstallFilePath() {
    std::string mcInstall = this->targetDir + "/mcgames/install.txt";
    return mcInstall;
}

bool ModeAdd::createTargetDirectory() {
    std::string mc = getMcGamesFolder();
    bool result = false;
    if (!Fs::exists(mc)) {
        std::cout << "Making " << mc << std::endl;
        result = Fs::makeDirectory(mc);
        if (!result) {
            std::cout << "Cannot create target" << std::endl;
        }
    }
    return result;
}

std::string ModeAdd::getMcGamesFolder() {
    std::string mc = this->targetDir + "/mcgames";
    return mc;
}

std::string ModeAdd::extractXMLText(tinyxml2::XMLElement *elem) {
    if (elem != nullptr) {
        if (elem->GetText() != nullptr) {
            return elem->GetText();
        }
    }
    return std::string();
}