#include <sys/stat.h>
#include <filesystem>
#include "Fs.h"

bool Fs::exists(const std::string& file) {
    struct stat buffer{};
    int result = (stat (file.c_str(), &buffer) == 0);
    return (bool)result;
}

bool Fs::makeDirectory(const std::string& dir) {
#ifdef __MINGW32__
    const int error = mkdir(dir.c_str());
#else
    const int error = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
    return -1 != error;
}

std::string winSlashes(std::string path) {
    std::replace(path.begin(),path.end(),'/','\\');
    return path;
}

bool Fs::remove(const std::string &file) {
    return std::filesystem::remove_all(file.c_str());
}

std::string Fs::getCurrentPath()
{
    std::string currentPath = std::filesystem::current_path().string();
    return currentPath;
}

std::string Fs::stem(const std::string &file) {
    std::string base = std::filesystem::path(file).stem().string();
    return base;
}

std::string Fs::basename(const std::string &file) {
    std::string base = std::filesystem::path(file).filename().string();
    return base;
}

std::string Fs::dirname(const std::string &file) {
    std::string dirname = std::filesystem::path(file).parent_path().string();
    return dirname;
}

std::string Fs::extension(const std::string &file) {
    std::string extension = std::filesystem::path(file).extension().string();
    return extension;
}

int Fs::copy(std::string source, std::string destination)
{
#ifdef __MINGW32__
    // Windows users... get forked!
    std::string cmd = "copy /Y " + source + " " + destination;
    system(cmd.c_str());
#else
    // Proper operating systems
    std::filesystem::copy_file(source, destination, std::filesystem::copy_options::overwrite_existing);
#endif
    return 0; // this is fine
}

int Fs::copyRecursive(const std::filesystem::path &src, const std::filesystem::path &target)
{
    try
    {
        std::filesystem::copy(src, target, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
    }
    catch (std::exception& e)
    {
    }
    return 0;
}

int Fs::filesize(std::string src) {
    return std::filesystem::file_size(src.c_str());
}
