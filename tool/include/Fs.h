#pragma once
#include <string>

class Fs
{
  public:
    static bool exists(const std::string& file);
    static bool makeDirectory(const std::string& dir);
    static bool remove(const std::string& file);
    static std::string basename(const std::string& file);
    static std::string dirname(const std::string& file);

    static int filesize(std::string src);
    static int copy(std::string source, std::string destination);

    static std::string extension(const std::string& file);

    static std::string stem(const std::string& file);

    static std::string getCurrentPath();

    static int copyRecursive(const std::string& src, const std::string& target);
};