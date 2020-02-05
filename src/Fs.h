#ifndef PANDORER_FILESYSTEM_H
#define PANDORER_FILESYSTEM_H

#include <string>
using namespace std;

class Fs {
public:
    static bool exists(const string& file);
    static bool makeDirectory(const string& dir);
    static bool unlink(const string& file);
    static string basename(const string& file);
    static string dirname(const string& file);

    int copy(string source, string destination);
};


#endif //PANDORER_FILESYSTEM_H
