#include <sys/stat.h>
#include "FileSystem.h"

bool FileSystem::exists(std::string file) {
    struct stat buffer{};
    int result = (stat (file.c_str(), &buffer) == 0);
    return (bool)result;
}

bool FileSystem::makeDirectory(const std::string& dir) {
#ifdef __MINGW32__
    const int error = mkdir(dir.c_str());
#else
    const int error = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
    return -1 != error;
}