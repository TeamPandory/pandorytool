#include "Sticks.h"
Sticks::Sticks() {
    sticks["jailbreak"] = {
            "jailbreak",
            "pandorytool-stick-jailbreak",
            "https://github.com/emuchicken/pandorytool/archive/stick-jailbreak.tar.gz",
            "This USB will patch your system to run `pandory.sh` off the USB drive when inserted.\n"
            "`pandory.sh` is a bash-shellscript. By default, it starts the android launcher, but can\n"
            "be configured to do anything you like. This means you can use this stick as a base to make your\n"
            "own sticks.\n\n"
            "After a successful jailbreak, the stick is reconfigured to act as a dedicated `Launch Android`-Stick.\n"
            "Insert this USB while booted. If the update gets stuck on a black screen with chinese text, \n"
            "reboot the machine and try again.\n"
    };

    sticks["backup"] = {
            "backup",
            "pandorytool-stick-backup",
            "https://github.com/emuchicken/pandorytool/archive/stick-backup.tar.gz",
            "This stick will backup your machine system/data-partitions to your USB drive\n"
            "Insert this USB while booted. If the update gets stuck on a black screen with chinese text, \n"
            "reboot the machine and try again."
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
}

stick Sticks::getStickByName(const std::string &stickName) {
    std::map<std::string, stick>::iterator it;
    for (it = sticks.begin(); it != sticks.end(); it++) {
        if (it->first == stickName) {
            return it->second;
        }
    }
    return stick{};
}
