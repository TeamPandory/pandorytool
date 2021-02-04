#ifndef PANDORY_SCREENSCRAPERXML_H
#define PANDORY_SCREENSCRAPERXML_H
#include <tinyxml2.h>
#include <string>

class ScreenScraperXML {
protected:
    tinyxml2:: XMLDocument doc;
    tinyxml2::XMLElement *game;
    FILE * xmlFile;

public:
    bool load(const std::string& filename);
    std::string getRomName();
    std::string getPlayers();
    std::string getDescription();
    std::string getGenre();
    std::string getCRC();
    int getYear();

    std::string getDeveloper();

    std::string getConsole();

    int getId();

    std::string getSuffix();
};
#endif //PANDORY_SCREENSCRAPERXML_H
