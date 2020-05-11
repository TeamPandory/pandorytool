#include "UserFolders.h"
#include <filesystem>

std::string UserFolders::getTemporaryFolder() {
    return std::filesystem::temp_directory_path().string();
}
