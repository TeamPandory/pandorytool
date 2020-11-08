#include <gtkmm.h>
#include "CommandLineArguments.h"
#include "PandoryTool.h"
#include "modes/ModeAdd.h"
#include "modes/ModePrepare.h"
#include "modes/ModePspfix.h"
#include "modes/ModeStick.h"
#include "FrmMain.h"

PandoryTool::PandoryTool(int i, char **pString) {
    args = CommandLineArguments(i, pString);
}

std::string PandoryTool::getCommitHash() {
    std::string version = GIT_COMMIT_HASH;
    if (version.empty()) {
        return "000000";
    }
    return version;
}

std::string PandoryTool::getCompileDate() {
    std::string compileDate = GIT_COMPILE_DATE;
    return compileDate;
}


std::string PandoryTool::getAppSuffix() {
    std::string suffix;
    if (editionCheck.isUltimate()) {
        suffix = "Ultimate";
    } else {
        suffix = "Freeware";
    }
    return suffix;
}

int PandoryTool::main(int argc, char **argv) {

    std::cout << "-----------------------------------------------------------------------------------------------------"
              << std::endl;
    std::cout << "Pandory Tool - Open your Pandora Games 3D" << " by emuchicken & dajoho        [" << getAppSuffix()
              << ": " << getCompileDate() << "/" << getCommitHash() << "]" << std::endl;
    std::cout << "== Join us on Discord! https://pg3d-hax.uk/discord" << std::endl;
    std::cout << "== Like us on Facebook! https://www.facebook.com/groups/2522039741415070/" << std::endl;
    std::cout << "== Visit us on PG3D-HAX! https://pg3d-hax.uk" << std::endl;
    std::cout << std::endl;

    if (editionCheck.isShareware()) {
        std::cout << "== Pandorytool has been worked on with blood, sweat and tears. If you would like us to continue "
                  << std::endl;
        std::cout
                << "== work on this tool, please consider grabbing us a coffee at https://www.buymeacoffee.com/CKZbiXa."
                << std::endl;
        std::cout
                << "== Patreons get early-access to new versions: https://pg3d-hax.uk/donate."
                << std::endl;
        std::cout << std::endl;
        std::cout << " * Various MAME cfgs contributed by the community (check each cfg for credits)" << std::endl;
    }
    std::cout << "-----------------------------------------------------------------------------------------------------"
              << std::endl;

    /*
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(
            argc,
            argv,
            "uk.pg3d-hax.pandory"
    );
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("gui.glade");

    FrmMain *frm;
    builder->get_widget_derived("frmMain", frm);
    int x = 0;
    app->run(*frm);
    return 0;
     */

    if (args.getArgumentCount() == 1) {
        usage();
        return 1;
    }

    std::string mode = args.getArgument(1);
    if (mode == "add") {
        return add();
    }

    if (mode == "prepare") {
        return prepare();
    }

    if (mode == "pspfix") {
        return pspFix();
    }

    if (mode == "stick") {
        return stick();
    }

    return 0;
}

void PandoryTool::usage() {
    std::cout << "Usage: " << std::endl;

    std::cout << "1) Put your ROMS in the correct subfolders and scrape them with Skraper:" << std::endl;
    std::cout << "   == Tutorial video [Using Skraper]     : https://www.youtube.com/watch?v=10naz1ZUOC4" << std::endl;
    std::cout << "   == Tutorial video [Advanced scraping] : https://www.youtube.com/watch?v=10naz1ZUOC4" << std::endl;
    std::cout << std::endl;

    std::cout
            << "2) => Take all the scraped ROMS from <sourceDir> and prepare them for your console in <destDir>."
            << std::endl;
    std::cout << "\t\tpandory add <sourceDir> <destDir>" << std::endl;
    std::cout << "\t\tExample: pandory add C:\\roms F:\\" << std::endl;
    std::cout << std::endl;

    std::cout << "-----------------------------------------------------------------------------------------------------"
              << std::endl;

    std::cout << "PANDORY JAILBREAK! - PLEASE BACK UP YOUR SYSTEM FIRST!" << std::endl;
    std::cout << "   == Tutorial video [Pandora MicroSD backup]: https://www.youtube.com/watch?v=sOluaeOtTX4"
              << std::endl;
    std::cout << "   == Tutorial video [Full system backups]   : https://www.youtube.com/watch?v=HdLaEymH0ok"
              << std::endl;
    std::cout << "   == Tutorial video [How to restore backups]: https://www.youtube.com/watch?v=02VBVWCTXgc"
              << std::endl << std::endl;

    std::cout << "3) => Create a `Backup-to-USB`-Stick that will backup your system/data partitions before jailbreaking"
              << std::endl;
    std::cout << "\t\tpandory stick backup <destDrive>" << std::endl;
    std::cout << "\t\tExample: pandory stick backup F:\\" << std::endl;
    std::cout << std::endl;

    std::cout << "4) => Create a `Jailbreak`-Stick that will patch your system and allow you to run any compatible"
              << std::endl;
    std::cout << "      application from USB." << std::endl;
    std::cout << "\t\tpandory stick jailbreak <destDrive>" << std::endl;
    std::cout << "\t\tExample: pandory stick jailbreak F:\\" << std::endl;
    std::cout << std::endl;

    std::cout << "-----------------------------------------------------------------------------------------------------"
              << std::endl;

    std::cout << "FIX PSP CONTROLS & TWO-PLAYER MODES!" << std::endl;
    std::cout << "Note: These fixes directly modify files on your SD card. Please make a backup before you"
              << std::endl;
    std::cout << "attempt any of these modifications!" << std::endl << std::endl;
    std::cout << "5) => Fix controls for inbuilt (stock) or pandory-added games" << std::endl;
    std::cout << "      Stage 1: Add some preparation files to your USB stick. Install this onto your Pandora Games 3D."
              << std::endl;
    std::cout << "\t\tpandory pspfix stage1 <destDrive>" << std::endl;
    std::cout << "      Stage 2: Take out your SD card after stage 1 and run stage 2 to fix your PSP configuration."
              << std::endl;
    std::cout << "\t\tpandory pspfix stage2 <destDrive>" << std::endl;
    std::cout << std::endl;
}

int PandoryTool::add() {
    std::string sourceDir = args.getPathArgument(2);
    std::string targetDir = args.getPathArgument(3);
    if (sourceDir.empty() || targetDir.empty()) {
        usage();
        return 1;
    }
    ModeAdd add(sourceDir, targetDir);
    return add.main();
}

int PandoryTool::prepare() {
    std::string sourceDir = args.getPathArgument(2);
    if (sourceDir.empty()) {
        usage();
        return 1;
    }
    ModePrepare prepare(sourceDir);
    return prepare.main();
}

int PandoryTool::pspFix() {
    std::string subMode = args.getArgument(2);
    std::string targetDir = args.getPathArgument(3);
    if (targetDir.empty() || subMode.empty()) {
        usage();
        return 1;
    }
    ModePspfix pspfix(targetDir);

    if (subMode == "stage1") {
        return pspfix.stage1();
    } else if (subMode == "stage2") {
        return pspfix.stage2();
    }
    usage();
    return 1;
}

int PandoryTool::stick() {
    std::string stickType = args.getArgument(2);
    std::string target = args.getPathArgument(3);
    if (stickType.empty() || target.empty()) {
        usage();
        return 1;
    }
    ModeStick stick(stickType, target);
    stick.main();
    return 0;
}

