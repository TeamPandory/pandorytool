#include "UserFolders.h"
#include <filesystem>
#include <iostream>

std::string UserFolders::getTemporaryFolder() {
    std::string tmpFolder = std::filesystem::temp_directory_path().string();
    std::cout << "TEMP FOLDER:" << tmpFolder << std::endl;
    return tmpFolder;
}
