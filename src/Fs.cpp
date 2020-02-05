#include <sys/stat.h>
#include <filesystem>
#include "Fs.h"

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
    std::string base = std::filesystem::path(file).filename();
    return base;
}

string Fs::dirname(const string &file) {
    std::string dirname = std::filesystem::path(file).parent_path();
    return dirname;
}

string Fs::getExtension(const string &file) {
    std::string extension = std::filesystem::path(file).extension();
    return extension;
}

int Fs::copy(std::string source, std::string destination)
{
    //std::filesystem::create_directories(targetParent);
    std::filesystem::copy_file(source, destination, std::filesystem::copy_options::overwrite_existing);
    return 0;
}