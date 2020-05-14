#include "StickExtractor.h"
#include "libarchive.h"
#include "Fs.h"
#include "UserFolders.h"
#include <algorithm>

int StickExtractor::exractToFolder(const downloadDefinition &stick, std::string &tarPath, std::string &targetFolder) {
    std::string curDir = Fs::getCurrentPath();

    UserFolders uf;
    std::string tmpDir = uf.getTemporaryFolder() + "/pandoryTemp/";
    Fs::remove(tmpDir);
    Fs::makeDirectory(tmpDir);

    chdir(tmpDir.c_str());
    const char * foo = tarPath.c_str();
    std::string extractedFolder = tmpDir + stick.path+"/";
    Fs::remove(extractedFolder);
    Fs::makeDirectory(extractedFolder);
    extract(foo);
    chdir(curDir.c_str());
#ifdef __MINGW32__
    std::string cmd = extractedFolder + "/*.* " + targetFolder;
    std::replace(cmd.begin(),cmd.end(),'/','\\');
    std::string execCmd = "xcopy /E " + cmd;
    system(execCmd.c_str());
#else
    Fs::copyRecursive(extractedFolder, targetFolder+"/");
#endif
    return 0;
}

