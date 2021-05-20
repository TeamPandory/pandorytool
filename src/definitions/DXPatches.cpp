#include "DXPatches.h"


bool DXPatches::isValidZip(std::string &zipPrefix) {
    std::string fileHash = getOriginalHash(zipPrefix);
    for (const auto& validHash: validHashes) {
        if (fileHash == validHash) {
            return true;
        }
    }
    return false;
}

std::string DXPatches::getOriginalHash(const std::string& file) {
    if (Fs::exists(file+".bak")) {
        return hash.md5_file(file+".bak");
    }
    return hash.md5_file(file+".zip");
}
