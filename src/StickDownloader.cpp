#include "StickDownloader.h"
#include <iostream>
#include "UserFolders.h"
#include <curl/curl.h>

size_t WriteCallback(char *ptr, size_t size, size_t nmemb, void *f) {
    FILE *file = (FILE *) f;
    return fwrite(ptr, size, nmemb, file);
};

std::string StickDownloader::download(const stick &stick) {
    UserFolders uf;
    std::string targetFile = uf.getTemporaryFolder() + stick.stickName + ".tar.gz";
    const char *url = stick.stickUrl.c_str();
    const char *filename = targetFile.c_str();
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    std::cout << targetFile << std::endl;
    return targetFile;
}
