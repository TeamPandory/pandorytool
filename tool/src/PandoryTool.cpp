#include "PandoryTool.h"
#include "CommandLineArguments.h"
#include "config.h"
#include "modes/ModeAdd.h"
#include "modes/ModePrepare.h"
#include "modes/ModePspfix.h"
#include "modes/ModeStick.h"
#include <cstdlib>
#include <iostream>
#include "termcolor/termcolor.hpp"

PandoryTool::PandoryTool(int i, char** pString)
{
    args = CommandLineArguments(i, pString);
}

std::string PandoryTool::getCommitHash()
{
    std::string version = GIT_VERSION;
    if (version.empty())
    {
        return "Dirty";
    }
    return version;
}

std::string PandoryTool::getCompileDate()
{
    return COMPILE_DATE;
}

std::string PandoryTool::getAppSuffix()
{
    return "Ultimate";
}

int PandoryTool::main(int argc, char** argv)
{
    int exitCode = EXIT_SUCCESS;
    showIntro();   

    if (args.getArgumentCount() == 1)
    {
        usage();
        showExit();
        return EXIT_FAILURE;
    }

    std::string mode = args.getArgument(1);
    if (mode == "add") {
        exitCode = add();
    }
    else if (mode == "prepare") {
        exitCode = prepare();
    }
    else if (mode == "pspfix") {
        exitCode = pspFix();
    } 
    else if (mode == "stick") {
        exitCode = stick();
    }
    return exitCode;
}

void PandoryTool::showIntro()
{
    std::cout << "-----------------------------------------------------------------------------------------------------"
              << std::endl;
    std::cout << termcolor::blue << "Pandory Tool - Open your Pandora Box" << termcolor::reset 
              << " by emuchicken & dajoho         [" << getAppSuffix() << ": " << getCompileDate() << "/"
              << getCommitHash() << "]" << std::endl;
}

void PandoryTool::showExit()
{
    std::cout << std::endl;
    std::cout << termcolor::magenta << "== Join us on " << "Discord" << termcolor::reset << "  https://teampandory.com/discord" << std::endl;
    std::cout << termcolor::blue    << "== Like us on " << "Facebook" << termcolor::reset << " https://www.facebook.com/groups/2522039741415070/" << std::endl;
    std::cout << termcolor::cyan    << "== Visit our website" << termcolor::reset << "   https://teampandory.com" << std::endl;
    std::cout << std::endl;

    std::cout << "Pandorytool has been worked on with blood, sweat and tears. If it has been useful to you,"
              << std::endl;

    std::cout << "please consider grabbing us a coffee at https://www.buymeacoffee.com/CKZbiXa." << std::endl;
    std::cout << "" << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------------------"
              << std::endl;
}

void PandoryTool::usage()
{
    std::cout << std::endl;
    std::cout << termcolor::green << "PANDORA GAMES 3D, 3D+, 3D GAMES AND CLONES (Pandory3D)" << termcolor::reset << std::endl;

     std::cout << R"(
Add games:
1) Put your ROMS in the correct subfolders

2) Take all the ROMS in <sourceDir> and prepare them for your console in <destDir>.
                pandory add <sourceDir> <destDir>
                Example: pandory add C:\roms F:\

PANDORY JAILBREAK! - IF POSSIBLE, PLEASE BACK UP YOUR SYSTEM FIRST!
   == Tutorial video [Pandora MicroSD backup]: https://www.youtube.com/watch?v=sOluaeOtTX4
   == Tutorial video [Full system backups]   : https://www.youtube.com/watch?v=HdLaEymH0ok
   == Tutorial video [How to restore backups]: https://www.youtube.com/watch?v=02VBVWCTXgc

1) Create a `Backup-to-USB`-Stick that will backup your system/data partitions before jailbreaking
                pandory stick backup <destDrive>
                Example: pandory stick backup F:\

2) Create a `Jailbreak`-Stick that will patch your system and allow you to run any compatible
      application from USB.
                pandory stick jailbreak <destDrive>
                Example: pandory stick jailbreak F:\

-----------------------------------------------------------------------------------------------------
FIX PSP CONTROLS & TWO-PLAYER MODES! *Only for PG3D and PG3D+ systems
Note: These fixes directly modify files on your SD card. Please make a backup before you
attempt any of these modifications!

Fix controls for inbuilt (stock) or pandory-added games
1) Add some preparation files to your USB stick. Install this onto your Pandora Games 3D.
                pandory pspfix stage1 <destDrive>
2) Take out your SD card after stage 1 and run stage 2 to fix your PSP configuration.
                pandory pspfix stage2 <destDrive>
)" << std::endl;

    std::cout << termcolor::yellow << "PANDORA BOX DX (PandoryDX)" << termcolor::reset << std::endl;

std::cout << R"(
      Install a set of improved settings to your Pandora DX micro-sd or usb-stick.
      WARNING: BACK UP YOUR SD-CARD/USB-STICK WITH WIN32IMAGER BEFORE YOU CONTINUE!

Insert Pandora Box DX microsd into computer, then type in:
                pandory stick dx <destDrive>
                Example: pandory stick dx F:\)" << std::endl;
}

int PandoryTool::add()
{
    std::string sourceDir = args.getPathArgument(2);
    std::string targetDir = args.getPathArgument(3);
    if (sourceDir.empty() || targetDir.empty())
    {
        usage();
        return 1;
    }
    ModeAdd add(sourceDir, targetDir);
    return add.main();
}

int PandoryTool::prepare()
{
    std::string sourceDir = args.getPathArgument(2);
    if (sourceDir.empty())
    {
        usage();
        return 1;
    }
    ModePrepare prepare(sourceDir);
    return prepare.main();
}

int PandoryTool::pspFix()
{
    std::string subMode = args.getArgument(2);
    std::string targetDir = args.getPathArgument(3);
    if (targetDir.empty() || subMode.empty())
    {
        usage();
        return 1;
    }
    ModePspfix pspfix(targetDir);

    if (subMode == "stage1")
    {
        return pspfix.stage1();
    }
    else if (subMode == "stage2")
    {
        return pspfix.stage2();
    }
    usage();
    return 1;
}

int PandoryTool::stick()
{
    std::string stickType = args.getArgument(2);
    std::string target = args.getPathArgument(3);
    if (stickType.empty() || target.empty())
    {
        usage();
        return 1;
    }
    ModeStick stick(stickType, target);
    stick.main();
    return 0;
}
