#include "definitions/Sticks.h"
Sticks::Sticks() {
    sticks["jailbreak"] = {
            "jailbreak",
            "",
            "",
            "Virtual stick definition"
    };

    sticks["backup"] = {
            "backup",
            "",
            "",
            "Virtual stick definition"
    };

    sticks["jailbreak3D"] = {
            "jailbreak3D",
            "pandory3D",
            "https://downloads.teampandory.com/pandory3D/jailbreak/pandory3D-jailbreak-20240714-2.0.tgz",
            "This USB will patch your system to run `pandory.sh` off the USB drive when inserted.\n"
            "`pandory.sh` is a bash-shellscript. It can be configured to do anything you like.\n\n"
            "Insert this USB while booted.\n"
            "The jailbreak also enables telnet on port 4444 and FTP on port 7777, which enables you to\n"
            "remotely log in using:\n\n"
            "telnet ip-of-pandora-box:4444"
    };

    sticks["jailbreak3DPlus"] = {
            "jailbreak3DPlus",
            "pandory3D",
            "https://downloads.teampandory.com/pandory3D/jailbreak/pandory3Dplus-jailbreak-20240714-2.0.tgz",
            "This USB will patch your system to run `pandory.sh` off the USB drive when inserted.\n"
            "`pandory.sh` is a bash-shellscript. It can be configured to do anything you like.\n\n"
            "Insert this USB while booted.\n"
            "The jailbreak also enables telnet on port 4444 and FTP on port 7777, which enables you to\n"
            "remotely log in using:\n\n"
            "telnet ip-of-pandora-box:4444"
    };

sticks["jailbreak7"] = {
            "jailbreak7",
            "pandorytool-jb7-1.14",
            "https://downloads.teampandory.com/pandorySeven/jailbreak/pandorySeven-jailbreak-20230629-d812db4.tgz",
            "The jailbreak also enables telnet on port 4444, which enables you to\n"
            "remotely log in using:\n"
            "telnet ip-of-pandora-box:4444\n\n"
            "WARNING: KEY7 CONSOLES DO NOT ALL HAVE A RECOVERY MODE\n"
            "AND YOU MAY NOT BE ABLE TO RECOVER YOUR SYSTEM IF SOMETHING\n"
            "GOES WRONG DURING THE JAILBREAK. THIS JAILBREAK COMES WITH NO WARRANTY!\n"
    };

    sticks["backup3D"] = {
            "backup3D",
            "pandorytool-stick-backup",
            "https://downloads.teampandory.com/pandory3D/backup/pandory3D-backup-20230629-d812db4.tgz",
            "This stick will backup your machine system/data-partitions to your USB drive\n"
            "Insert this USB while booted. If the update gets stuck on a black screen with chinese text, \n"
            "reboot the machine and try again."
    };

    sticks["backup3DPlus"] = {
            "backup3DPlus",
            "pOTAtoPlus-backup",
            "https://downloads.teampandory.com/pandory3D/backup/pandory3Dplus-backup-20230629-d812db4.tgz",
            "This stick will backup your machine system/data-partitions to your USB drive\n"
            "Insert this USB while booted. A chinese progress bar will appear. Leave it for 20-30 minutes! \n"
            "The progress bar will not move. You may need TWO attempts for the backup to start."
    };

    sticks["reicast"] = {
            "reicast",
            "pandory-jailbreak-reicast-master",
            "https://github.com/emuchicken/pandory-jailbreak-reicast/archive/master.tar.gz",
    };

    sticks["ppsspp"] = {
            "ppsspp",
            "pandory-jailbreak-ppsspp-master",
            "https://github.com/emuchicken/pandory-jailbreak-ppsspp/archive/master.tar.gz",
    };

    sticks["dx"] = {
            "dx",
            "dx",
            "https://teampandory.com/downloads/dx/dxFR1.tar.gz",
    };
}

downloadDefinition Sticks::getStickByName(const std::string &name) {
    std::map<std::string, downloadDefinition>::iterator it;
    for (it = sticks.begin(); it != sticks.end(); it++) {
        if (it->first == name) {
            return it->second;
        }
    }
    return downloadDefinition{};
}
