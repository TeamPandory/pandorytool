#pragma once
#include "Fs.h"
#include "Hash.h"
#include <sstream>
#include <string>
#include <tinyxml2.h>

class ScreenScraper
{
  public:
    void setUsername(const std::string& scraperUsername);
    void setPassword(const std::string& scraperPassword);
    void setScraperSystemId(int scraperId);
    void setDestinationFolder(const std::string& destinationFolder);
    int scrape();

    bool isValid() const;
    std::string dumpXML();
    std::string downloadVideo();
    std::string downloadScreenshot();
    void setRomFilename(const std::string& filename);
    void setRomHash(const std::string& md5Hash);

    const std::string& getXmlPath() const;

  protected:
    bool valid = false;
    std::ostringstream xmlContent;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* game;
    tinyxml2::XMLElement* medias;
    tinyxml2::XMLElement* system;
    std::string romFilename;
    std::string romHash;
    std::string xmlPath;
    Hash hash;
    std::string getUrl();
    std::string username;
    std::string password;
    std::string destFolder;
    int gameId;
    int systemId;
    int scraperSystemId;
    void parseGame(tinyxml2::XMLElement* data);
    void removeUserData(tinyxml2::XMLElement* data);
    void removeServerData(tinyxml2::XMLElement* data);
    void removeMediaContent(tinyxml2::XMLElement* data);
    static void downloadFile(const std::string& url, const std::string& filename);
    std::string downloadVideo(const std::string& video);
};