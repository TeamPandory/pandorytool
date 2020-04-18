#include "StickExtractor.h"
#include "libarchive.h"
#include "Fs.h"

int StickExtractor::exractToFolder(std::string &stickType, std::string &targetFolder) {
    std::string curDir = Fs::getCurrentPath();
    std::string tarPath = curDir + "/sticks/stick-" + stickType + ".tar.gz";
    std::string tmpDir = curDir + "/tmp/";
    Fs::remove(tmpDir);
    Fs::makeDirectory(tmpDir);

    chdir(tmpDir.c_str());
    extract(tarPath.c_str());

    std::string extractedFolder = tmpDir+"pandorytool-stick-"+stickType;
    chdir(curDir.c_str());
    Fs::copyRecursive(extractedFolder, targetFolder);
    return 0;
}
