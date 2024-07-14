#pragma once
#include <string>

class UserFolders
{
  public:
    std::string getTemporaryFolder();

    void GetUserLocalTempPath(std::wstring& input_parameter);
};