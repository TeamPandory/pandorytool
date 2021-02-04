#ifndef PANDORERAPP_H
#define PANDORERAPP_H

#include "EditionCheck.h"

class PandoryTool {
protected:
    EditionCheck editionCheck;
    CommandLineArguments args = CommandLineArguments(0, nullptr);
public:
    PandoryTool(int i, char **pString);
    static void usage();
    int add();
    int prepare();
    int main(int argc, char **argv);

    std::string getCommitHash();

    std::string getAppSuffix();

    int stick();
    int pspFix();

    std::string getCompileDate();
};

#endif //PANDORERAPP_H
