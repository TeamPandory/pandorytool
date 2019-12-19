#ifndef TESTC_PANDORERAPP_H
#define TESTC_PANDORERAPP_H


class PandoryTool {
protected:
    CommandLineArguments args = CommandLineArguments(0, nullptr);
public:
    PandoryTool(int i, char **pString);
    static void usage();
    int add();
    int main();
};


#endif //TESTC_PANDORERAPP_H
