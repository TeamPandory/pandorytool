#include <sys/stat.h>
#include <filesystem>
#include <iostream>
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
    std::string cmd = "copy /Y \"" + winSlashes(source + "\" " + destination + " > NUL");
    system(cmd.c_str());
#else
    // Proper operating systems
    std::filesystem::copy_file(source, destination, std::filesystem::copy_options::overwrite_existing);
#endif
    return 0; // this is fine
}

int Fs::copyRecursive(const std::filesystem::path &src, const std::filesystem::path &target)
{
    std::filesystem::path copySrc = src.lexically_normal();
    std::filesystem::path copyTarget = target.lexically_normal();

    try
    {
#ifdef __MINGW32__
        // Windows users... get forked!
        // It is terrible we have to do this to get reliable copy_recursive.
        std::string cmd = "xcopy /E /Y \"" + copySrc.string() + "\" \"" + copyTarget.string() + "\" > NUL";
        system(cmd.c_str());
#else
        std::filesystem::copy(copySrc, copyTarget, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
#endif

    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

int Fs::filesize(std::string src) {
    return std::filesystem::file_size(src.c_str());
}
