#ifndef PANDORERAPP_H
#define PANDORERAPP_H

class PandoryTool {
protected:
    CommandLineArguments args = CommandLineArguments(0, nullptr);
public:
    PandoryTool(int i, char **pString);
    static void usage();
    int add();
    int prepare();
    int main();

    std::string getCommitHash();

    std::string getAppSuffix();
};

#endif //PANDORERAPP_H
