#include "ScreenScraperXML.h"

bool ScreenScraperXML::load(const std::string &filename) {
    xmlFile = fopen(filename.c_str(), "rb");
    doc.LoadFile(xmlFile);
    tinyxml2::XMLElement *data = doc.FirstChildElement("Data");
    if (data != nullptr) {
        game = data->FirstChildElement("jeu");
        if (game != nullptr) {
            return true;
        }
    }
    return false;
}

std::string ScreenScraperXML::getRomName() {
    tinyxml2::XMLElement *names = game->FirstChildElement("noms");
    int i = 0;
    std::string romName;
    for (tinyxml2::XMLElement *name = names->FirstChildElement("nom");
         name != nullptr;
         name = name->NextSiblingElement("nom")) {
        if (i == 0) {
            romName = name->GetText();
        }
        const char *rawName = name->Attribute("region");
        if (rawName != nullptr) {
            std::string nameStr(rawName);
            if (nameStr == "wor") {
                romName = name->GetText();
                break;
            }
        }
        i++;
    }
    return romName;
}
