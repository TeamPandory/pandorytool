#include "UserFolders.h"
#include <filesystem>
#include <iostream>

std::string UserFolders::getTemporaryFolder() {
#ifdef __MINGW32__
    std::string tmpFolder = getenv("TEMP");
    tmpFolder = tmpFolder + "/";
#else
    std::string tmpFolder = std::filesystem::temp_directory_path().string();
#endif
    return tmpFolder;
}
