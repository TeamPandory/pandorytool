#pragma once
#include "CommandLineArguments.h"
#include "EditionCheck.h"
#include <string>

class PandoryTool
{
  protected:
    EditionCheck editionCheck;
    CommandLineArguments args = CommandLineArguments(0, nullptr);

  public:
    PandoryTool(int i, char** pString);
    void showIntro();
    void showExit();
    void usage();
    int add();
    int prepare();
    int main(int argc, char** argv);

    std::string getCommitHash();

    std::string getAppSuffix();

    int stick();
    int pspFix();

    std::string getCompileDate();
};
