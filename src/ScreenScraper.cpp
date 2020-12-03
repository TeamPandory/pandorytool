#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <string>
#include <fstream>
#include "ScreenScraper.h"

void ScreenScraper::setUsername(const std::string &username) {
    ScreenScraper::username = username;
}

void ScreenScraper::setPassword(const std::string &password) {
    ScreenScraper::password = password;
}

void ScreenScraper::setDestinationFolder(const std::string &destFolder) {
    ScreenScraper::destFolder = destFolder;
}

void ScreenScraper::setRomFilename(const std::string &filename) {
    ScreenScraper::romFilename = filename;
}

void ScreenScraper::setRomHash(const std::string &md5Hash) {
    romHash = md5Hash;
}

int ScreenScraper::scrape() {
    valid = false;
    std::string url = getUrl();
    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;
        request.setOpt(new curlpp::options::Url(url));
        //request.setOpt(new curlpp::options::Verbose(true));
        curlpp::options::WriteStream ws(&xmlContent);
        request.setOpt(ws);
        request.perform();
        doc.Parse(xmlContent.str().c_str());
        data = doc.FirstChildElement("Data");
        if (data != nullptr) {
            removeUserData();
            removeServerData();
            removeMediaContent();
            parseGame();
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
    if (romHash.empty()) {
        md5Hash = hash.md5_file(romFilename);
        base = fs.basename(romFilename);
    } else {
        md5Hash = romHash;
        base = "";
    }
    url = "https://www.screenscraper.fr/api2/jeuInfos.php?devid=Bkg2k&devpassword=H2j26mjFnBN6tFDg"
          "&ssid=" + username + "&sspassword=" + password + "&softname=SkraperUI-1.1.20154&output=xml&neoforceupdate=0"
                                                            "&romtype=rom&romnom=" + base + "&md5=" + md5Hash;
    return url;
}

void ScreenScraper::parseGame() {
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
            int x = 0;
        }
    }
}


int ScreenScraper::getGameId() const {
    return gameId;
}

bool ScreenScraper::isValid() const {
    return valid;
}

int ScreenScraper::dumpXML() {
    tinyxml2::XMLPrinter printer;
    doc.Print(&printer);
    std::string gameXmlFile = std::to_string(gameId) + ".xml";
    std::ofstream gameXmlStream;
    std::string destRomFolder = destFolder + "/" + std::to_string(gameId);
    fs.makeDirectory(destRomFolder);
    std::string destFile = destRomFolder + "/" + gameXmlFile;
    if (fs.exists(destFile)) {
        return 1;
    }
    gameXmlStream.open(destFile);
    std::string xmlData = printer.CStr();
    gameXmlStream << xmlData;
    gameXmlStream.close();
    return 0;
}

void ScreenScraper::removeServerData() {
    tinyxml2::XMLElement *serveurs = data->FirstChildElement("serveurs");
    if (serveurs != nullptr) {
        serveurs->Parent()->DeleteChild(serveurs);
    }
}

void ScreenScraper::removeUserData() {
    tinyxml2::XMLElement *ssuser = data->FirstChildElement("ssuser");
    if (ssuser != nullptr) {
        ssuser->Parent()->DeleteChild(ssuser);
    }
}

void ScreenScraper::removeMediaContent() {
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

void ScreenScraper::downloadAll() {
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
            if (type == "video" || type == "ss" || type == "sstitle" || type == "screenmarquee") {
                if (filetype == "png" || filetype == "jpg") {
                    const char *attrRegion = media->Attribute("region");
                    const char *attrVersion = media->Attribute("version");
                    std::string region, version;
                    if (attrRegion != nullptr) {
                        region = attrRegion;
                    }
                    if (attrVersion != nullptr) {
                        version = attrVersion;
                    }
                    downloadImage(type, region, version, filetype);
                } else if (filetype == "mp4" && type == "video") {
                    downloadVideo(type);
                }
            }
        }
    }
}

void ScreenScraper::downloadImage(const std::string &type, const std::string &region, const std::string &version, const std::string &filetype) {
    const char *versionTmp = version.c_str();
    CURL *curl = nullptr;
    versionTmp = curl_easy_escape(curl, versionTmp, version.length());
    std::string escapedVersion = std::string(versionTmp);

    std::string url = "https://screenscraper.fr/image.php?gameid=" + std::to_string(gameId) +
                      "&media=" + type + "&hd=0&region=" + region + "&num=&version="+escapedVersion+"&maxwidth=5000&maxheight=5000";
    std::string targetFolder = destFolder + "/" + std::to_string(gameId);
    std::string targetFileName = targetFolder + "/" + std::to_string(gameId) + "." + type;
    if (!region.empty()) {
        targetFileName.append("." + region);
    }
    if (!version.empty()) {
        targetFileName.append("." + version);
    }

    targetFileName.append("." + filetype);
    fs.makeDirectory(targetFolder);
    downloadFile(url, targetFileName);
}

void ScreenScraper::downloadVideo(const std::string &video) {
    std::string url = "https://screenscraper.fr/medias/" + std::to_string(systemId) +
                      "/" + std::to_string(gameId) + "/video.mp4";
    std::string targetFolder = destFolder + "/" + std::to_string(gameId);
    std::string targetFileName = targetFolder + "/" + std::to_string(gameId) + ".mp4";
    fs.makeDirectory(targetFolder);
    downloadFile(url, targetFileName);
}


void ScreenScraper::downloadFile(const std::string &url, const std::string &filename) {
    try {
        std::ofstream targetFile;
        targetFile.open(filename);
        std::cout << "  Downloading: " << url << std::endl;

        curlpp::Cleanup cleaner;
        curlpp::Easy request;
        std::list<std::string> headers;
        headers.emplace_back(
                "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:82.0) Gecko/20100101 Firefox/82.0");
        request.setOpt(new curlpp::options::HttpHeader(headers));
        request.setOpt(new curlpp::options::Url(url));
        //request.setOpt(new curlpp::options::Verbose(true));

        curlpp::options::WriteStream ws(&targetFile);
        request.setOpt(ws);
        request.perform();

        targetFile.close();
    } catch (curlpp::RuntimeError &e) {
        std::cout << "Curl Runtime Error" << std::endl;
    } catch (curlpp::LogicError &e) {
        std::cout << "Curl Logic Error" << std::endl;
    }
}
