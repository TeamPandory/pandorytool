#include "Fs.h"
#include <algorithm>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <filesystem>
#include <string>
#include <sys/stat.h>

bool Fs::exists(const std::string& file)
{
    return boost::filesystem::exists(file);
}

bool Fs::makeDirectory(const std::string& dir)
{
    return boost::filesystem::create_directory(dir);
}

std::string winSlashes(std::string path)
{
    std::replace(path.begin(), path.end(), '/', '\\');
    return path;
}

bool Fs::remove(const std::string& file)
{
    return boost::filesystem::remove_all(file);
}

std::string Fs::getCurrentPath()
{
    std::string currentPath = std::filesystem::current_path().string();
    return currentPath;
}

std::string Fs::stem(const std::string& file)
{
    std::string base = std::filesystem::path(file).stem().string();
    return base;
}

std::string Fs::basename(const std::string& file)
{
    std::string base = std::filesystem::path(file).filename().string();
    return base;
}

std::string Fs::dirname(const std::string& file)
{
    std::string dirname = std::filesystem::path(file).parent_path().string();
    return dirname;
}

std::string Fs::extension(const std::string& file)
{
    return boost::filesystem::extension(file);
}

int Fs::copy(std::string source, std::string destination)
{
    // 107100 is ubuntu focal
    #if BOOST_VERSION > 107100
        return boost::filesystem::copy_file(source, destination, boost::filesystem::copy_options::overwrite_existing);
    #else
        return boost::filesystem::copy_file(source, destination, boost::filesystem::copy_options::overwrite_if_exists);
    #endif
}

int Fs::copyRecursive(const std::string& src, const std::string& target)
{
    boost::filesystem::path copySrc(src);
    boost::filesystem::path copyTarget(target);

    try
    {
        boost::filesystem::copy(copySrc.lexically_normal(), copyTarget.lexically_normal(),
                                boost::filesystem::copy_options::overwrite_existing
                                    | boost::filesystem::copy_options::recursive);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

int Fs::filesize(std::string src)
{
    return boost::filesystem::file_size(src);
}