#pragma once
#include <string>

class ModePrepare
{
  protected:
    std::string& sourceDir;

  public:
    explicit ModePrepare(std::string& sourceDir);
    int main();

    int mkdir(std::string systemType);
};