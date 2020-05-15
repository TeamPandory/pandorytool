#ifndef PANDORY_USERFOLDERS_H
#define PANDORY_USERFOLDERS_H
#include <string>

class UserFolders {


public:
    std::string getTemporaryFolder();

    void GetUserLocalTempPath(std::wstring &input_parameter);
};

#endif //PANDORY_USERFOLDERS_H
