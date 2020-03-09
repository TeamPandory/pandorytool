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

    void LogGitCommitHash();

    std::string getCommitHash();
};

#endif //PANDORERAPP_H
