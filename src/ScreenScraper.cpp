#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Exception.hpp>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "ScreenScraper.h"
#include "../config.h"


size_t scrapeWriteCallback(char *ptr, size_t size, size_t nmemb, void *f) {
    FILE *file = (FILE *) f;
    return fwrite(ptr, size, nmemb, file);
};

void ScreenScraper::setUsername(const std::string &scraperUsername) {
    ScreenScraper::username = scraperUsername;
}

void ScreenScraper::setPassword(const std::string &scraperPassword) {
    ScreenScraper::password = scraperPassword;
}

void ScreenScraper::setDestinationFolder(const std::string &destinationFolder) {
    ScreenScraper::destFolder = destinationFolder;
}

void ScreenScraper::setRomFilename(const std::string &filename) {
    ScreenScraper::romFilename = filename;
}

void ScreenScraper::setRomHash(const std::string &md5Hash) {
    romHash = md5Hash;
}

int ScreenScraper::scrape() {
    valid = false;
    xmlPath = "";
    std::string url = getUrl();
    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;
        request.setOpt(new curlpp::options::Url(url));
        request.setOpt(new curlpp::options::SslVerifyHost(false));
        request.setOpt(new curlpp::options::SslVerifyPeer(false));
        request.setOpt(new curlpp::options::ConnectTimeout(300));
        request.setOpt(new curlpp::options::Timeout (300));
        //request.setOpt(new curlpp::options::Verbose(true));
        curlpp::options::WriteStream ws(&xmlContent);
        request.setOpt(ws);
        request.perform();
        int http_code = curlpp::infos::ResponseCode::get(request);
        if (http_code == 500) {
            return 500;
        }

        std::string xmlString = xmlContent.str();
        doc.Parse(xmlString.c_str());
        tinyxml2::XMLElement *data;
        data = doc.FirstChildElement("Data");
        if (data != nullptr) {
            removeUserData(data);
            removeServerData(data);
            removeMediaContent(data);
            parseGame(data);
        }
    } catch (curlpp::RuntimeError &e) {
        std::cout << "Runtime error parsing:" << url << e.what() << std::endl;
        return 1;
    } catch (curlpp::LogicError &e) {
        std::cout << "Runtime error parsing:" << romFilename << e.what() << std::endl;
        return 1;
    }
    return 0;
}

std::string ScreenScraper::getUrl() {
    std::string url;
    std::string md5Hash;
    std::string base;
    base = Fs::basename(romFilename);
    md5Hash = hash.md5_file(romFilename);

    std::string devId = SCRAPE_USERNAME;
    std::string devPw = SCRAPE_PASSWORD;
    std::string scrapeUrl = SCRAPE_URL;
    url = scrapeUrl + "?devid="+ devId +"&devpassword=" + devPw +
          "&ssid=" + username + "&sspassword=" + password + "&softname=SkraperUI-1.1.20154&output=xml&neoforceupdate=0"
                                                            "&romtype=rom&romnom=" + curlpp::escape(base) + "&md5=" + md5Hash + "&systemeid=" + std::to_string(scraperSystemId);
    int x=1;
    std::cout << url << std::endl;
    return url;
}

void ScreenScraper::parseGame(tinyxml2::XMLElement *data) {
    game = data->FirstChildElement("jeu");
    if (game != nullptr) {
        const char *id = game->Attribute("id");
        if (id != nullptr) {
            gameId = std::atoi(id);
            // xml is valid enough to work with
            valid = true;
            medias = game->FirstChildElement("medias");
            system = game->FirstChildElement("systeme");
            const char *sysId = system->Attribute("id");
            systemId = std::atoi(sysId);
        }
    }
}

bool ScreenScraper::isValid() const {
    return valid;
}

std::string ScreenScraper::dumpXML() {
    tinyxml2::XMLPrinter printer;
    doc.Print(&printer);
    std::string gameXmlFile = std::to_string(gameId) + ".xml";
    std::ofstream gameXmlStream;
    std::string destRomFolder = destFolder + "/" + std::to_string(gameId);
    Fs::makeDirectory(destRomFolder);
    std::string destFile = destRomFolder + "/" + gameXmlFile;
    gameXmlStream.open(destFile);
    std::string xmlData = printer.CStr();
    gameXmlStream << xmlData;
    gameXmlStream.close();
    xmlPath = destFile;
    return destFile;
}

void ScreenScraper::removeServerData(tinyxml2::XMLElement *data) {
    tinyxml2::XMLElement *serveurs = data->FirstChildElement("serveurs");
    if (serveurs != nullptr) {
        serveurs->Parent()->DeleteChild(serveurs);
    }
}

void ScreenScraper::removeUserData(tinyxml2::XMLElement *data) {
    tinyxml2::XMLElement *ssuser = data->FirstChildElement("ssuser");
    if (ssuser != nullptr) {
        ssuser->Parent()->DeleteChild(ssuser);
    }
}

void ScreenScraper::removeMediaContent(tinyxml2::XMLElement *data) {
    tinyxml2::XMLElement *tmpGame = data->FirstChildElement("jeu");
    if (tmpGame != nullptr) {
        tinyxml2::XMLElement *tmpMedias = tmpGame->FirstChildElement("medias");
        if (tmpMedias != nullptr) {
            for (tinyxml2::XMLElement *media = tmpMedias->FirstChildElement("media");
                 media != nullptr;
                 media = media->NextSiblingElement("media")) {
                media->SetText("");
            }
        }
    }
}

std::string ScreenScraper::downloadVideo() {
    if (medias != nullptr) {
        for (tinyxml2::XMLElement *media = medias->FirstChildElement("media");
             media != nullptr;
             media = media->NextSiblingElement("media")) {

            std::string filetype = media->Attribute("format");
            std::string parent = media->Attribute("parent");
            if (parent != "jeu") {
                // not interesting media
                continue;
            }
            std::string type = media->Attribute("type");

            if (type == "video") {
                if (filetype == "mp4" && type == "video") {
                    return downloadVideo(type);
                }
            }
        }
    }
    return std::string();
}


std::string ScreenScraper::downloadVideo(const std::string &video) {
    std::string url = "https://screenscraper.fr/medias/" + std::to_string(systemId) +
                      "/" + std::to_string(gameId) + "/video.mp4";
    std::string targetFolder = destFolder + "/" + std::to_string(gameId);
    std::string targetFileName = targetFolder + "/" + std::to_string(gameId) + ".mp4";
    Fs::makeDirectory(targetFolder);
    if (!Fs::exists(targetFileName)) {
        downloadFile(url, targetFileName);
    }
    return targetFileName;
}


void ScreenScraper::downloadFile(const std::string &url, const std::string &filename) {
    CURL *curl;
    FILE *fp;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename.c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, scrapeWriteCallback);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:84.0) Gecko/20100101 Firefox/84.0");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 300);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 300);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

const std::string &ScreenScraper::getXmlPath() const {
    return xmlPath;
}

void ScreenScraper::setScraperSystemId(int scraperId) {
    ScreenScraper::scraperSystemId = scraperId;
}
