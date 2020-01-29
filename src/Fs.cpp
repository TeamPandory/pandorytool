#include <sys/stat.h>
#include <filesystem>
#include "Fs.h"
using namespace std;

bool Fs::exists(const string& file) {
    struct stat buffer{};
    int result = (stat (file.c_str(), &buffer) == 0);
    return (bool)result;
}

bool Fs::makeDirectory(const string& dir) {
#ifdef __MINGW32__
    const int error = mkdir(dir.c_str());
#else
    const int error = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
    return -1 != error;
}

bool Fs::unlink(const string &file) {
    return (bool) remove(file.c_str());
}

string Fs::basename(const string &file) {
    string base = std::filesystem::path(file).filename();
    return base;
}
