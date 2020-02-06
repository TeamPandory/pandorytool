#ifndef PANDORER_FILESYSTEM_H
#define PANDORER_FILESYSTEM_H

#include <string>
using namespace std;

class Fs {
public:
    static bool exists(const string& file);
    static bool makeDirectory(const string& dir);
    static bool remove(const string& file);
    static string basename(const string& file);
    static string dirname(const string& file);

    static int filesize(std::string src);
    static int copy(string source, string destination);

    static string getExtension(const string &file);
};


#endif //PANDORER_FILESYSTEM_H
