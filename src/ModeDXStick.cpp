#include <iostream>
#include <curl/curl.h>
#include "ModeDXStick.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <thread>
#include "libarchive.h"
#include "UserFolders.h"


int dxWriteCount = 0;
size_t dlWriteCallback(char *ptr, size_t size, size_t nmemb, void *f) {
    FILE *file = (FILE *) f;
    if (dxWriteCount % 4 == 0) {
        std::cout << ".";
    }
    dxWriteCount++;
    if (dxWriteCount % 400 == 0) {
        std::cout << std::endl;
    }
    return fwrite(ptr, size, nmemb, file);
};

void ModeDXStick::downloadFile(const std::string &url, const std::string &filename) {
    CURL *curl;
    FILE *fp;
    curl = curl_easy_init();
    dxWriteCount = 0;
    if (curl) {
        /* Copy/waste from StickDownloader. This will be refactored soon. */
        fp = fopen(filename.c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, dlWriteCallback);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:84.0) Gecko/20100101 Firefox/84.0");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6000);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 6000);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

std::string ModeDXStick::downloadPatchFile(const std::string &patchName, const std::string &target)
{
    UserFolders uf;
    std::string targetFile = uf.getTemporaryFolder() + patchName + ".tgz";
    std::string lowerCase = patchName;
    std::string patchUrl = "https://pg3d-hax.uk/downloads/dx/patches/1.11/";
    std::cout << "Downloading "<< patchName << " patch file:" << std::endl;
    std::transform(lowerCase.begin(), lowerCase.end(), lowerCase.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    downloadFile(patchUrl + lowerCase, targetFile);
    std::cout << std::endl << std::endl;
    return targetFile;
}

int ModeDXStick::startDXPatch(std::string &target) {
    UserFolders uf;
    std::string base = "roms";
    if (Fs::exists(target+"/pandory_backups/hadc.zip")) {
        base = "/pandory_backups/";
    }
    std::string had = target+"/"+base+"/had";
    std::string hadc = target+"/"+base+"/hadc";
    std::string rade = target+"/"+base+"/rade";

    if (!Fs::exists(had+".zip") || !Fs::exists(hadc+".zip") || !Fs::exists(rade+".zip")) {
        std::cout << "Cannot detect your DX USB stick/SD card at location: " + target << std::endl;
        std::cout << "Please make sure it is inserted. " << std::endl;
        exit;
    } else {
        std::cout << "Checking if your DX storage is compatible. This may take a moment..." << std::endl;
        if (!dxPatches.isValidZip(had) || !dxPatches.isValidZip(hadc) || !dxPatches.isValidZip(rade)) {
            std::cout << "Your DX storage medium seems to be incompatible or has already been patched." << std::endl;
            if (Fs::exists(target+"/pandory_backups/had.zip")) {
                std::cout << "This device contains backup files in \"pandory_backups\". Restore these if" << std::endl;
                std::cout << "you need to re-patch or reset your DX." << std::endl;
            }
            std::cout << std::endl;
            std::cout << "If you still have trouble, please contact @dajoho or @emuchicken via Discord." << std::endl;
            std::cout << "https://pg3d-hax.uk/discord" << std::endl;
            exit;
        } else {
            std::string hadHash = hash.md5_file(had+".zip");
            std::string hadcHash = hash.md5_file(hadc+".zip");
            std::string radeHash = hash.md5_file(rade+".zip");

            std::cout << "Counting potatoes ";
            for (int i=0;i<3;i++) {
                std::cout << "." << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(400));
            }
            std::cout << " 1!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            std::cout << "Found a supported DX storage device in " << target << ". Let's rock!" << std::endl << std::endl;
            int x;
            std::cout << "Pandory needs a bit of space. Would you like to delete the PS1 Barbie Explorer game? [Y/N]" << std::endl;
            while ((x = getchar())) {
                if (x == 121 || x == 89) {
                    // delete
                    std::cout << "Removing useless ROM \"Barbie-Explorer\" ..." << std::endl;
                    unlink(std::string(target+"/romsp/Barbie-Explorer.bin").c_str());
                    unlink(std::string(target+"/romsp/Barbie-Explorer.srm").c_str());
                    break;
                }
                if (x == 78 || x == 110) {
                    // don't delete. just soldier on.
                    break;
                }
            }

            std::cout << "Downloading PandoryDX release data..." << std::endl;
            std::string dxTmp = uf.getTemporaryFolder() + "pandoryDX.tgz";
            downloadFile("https://pg3d-hax.uk/downloads/dx/releases/pandoryDX-1.11.tgz", dxTmp);
            std::cout << std::endl << std::endl;

            std::string hadTmp = downloadPatchFile(hadHash, target);
            std::string hadcTmp = downloadPatchFile(hadcHash, target);
            std::string radeTmp = downloadPatchFile(radeHash, target);

            std::string backupFolder = target + "/pandory_backups";
            Fs::makeDirectory(backupFolder);
            if (!Fs::exists(backupFolder+"/demo.avi")) {
                backup(target, "demo.avi", backupFolder);
                backup(target, "demo_384x224.avi", backupFolder);
                backup(target, "demo_640x480.avi", backupFolder);
                backup(target, "demo_1024x600.avi", backupFolder);
                backup(target, "demo_en.avi", backupFolder);
                backup(target, "demo_en_384x224.avi", backupFolder);
                backup(target, "demo_en_640x480.avi", backupFolder);
                backup(target, "demo_en_1024x600.avi", backupFolder);
                backup(target, "user_bg.bmp", backupFolder);
                backup(target + "/roms/", "had.zip", backupFolder);
                backup(target + "/roms/", "hadc.zip", backupFolder);
                backup(target + "/roms/", "rade.zip", backupFolder);
                std::cout << std::endl;
            }

            std::string curDir = Fs::getCurrentPath();
            // Extract patches.
            std::string targetDir = target + "/roms";
            std::cout << "Extracting patch data: 0%" << std::endl;
            chdir(targetDir.c_str());
            std::cout << "Extracting patch data: 30%" << std::endl;
            extract(hadTmp.c_str());
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            std::cout << "Extracting patch data: 70%" << std::endl;
            extract(hadcTmp.c_str());
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            std::cout << "Extracting patch data: 100%" << std::endl << std::endl;
            extract(radeTmp.c_str());
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            Fs::remove(hadTmp);
            Fs::remove(hadcTmp);
            Fs::remove(radeTmp);
            chdir(curDir.c_str());

            chdir(target.c_str());
            // Cleanup old FR1/110 files
            if (Fs::exists("pandory/pandory.sh")) {
                std::cout << "Cleaning up old Pandory DX FR1/1.10 files... (they're in pandory_backups now!!)" << std::endl << std::endl;

                if (Fs::exists("pandory/pandory-options.cfg-noaccelerate")) {
                    moveOld("pandory", "pandory_backups/pandory_110");
                }
            }
            chdir(curDir.c_str());


            chdir(target.c_str());
            std::cout << "Extracting Pandory DX release data..." << std::endl << std::endl;

            extract(dxTmp.c_str());
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            chdir(curDir.c_str());


            std::cout << "PandoryDX has been successfully installed to your storage medium." << std::endl;
            std::cout << "All original files have been copied to the pandory_backups folder." << std::endl << std::endl;
        }
    }
    return 0;
}

bool ModeDXStick::backup(const std::string &srcFolder, const std::string &srcFile, const std::string &backupFolder) {
    std::string sourceFile = srcFolder + srcFile;
    std::cout << "Backing up " << srcFile << " to folder 'pandory_backups'" << std::endl;
    if (Fs::exists(sourceFile)) {
        Fs::copy(sourceFile, backupFolder + "/" + srcFile);
    }
    return true;
}

bool ModeDXStick::moveOld(const std::string &srcFile, const std::string &destFile) {
    return rename(srcFile.c_str(), destFile.c_str());
}


