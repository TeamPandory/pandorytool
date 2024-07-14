#include "ScreenScraperXML.h"

bool ScreenScraperXML::load(const std::string& filename)
{
    xmlFile = fopen(filename.c_str(), "rb");
    doc.LoadFile(xmlFile);
    fclose(xmlFile);
    tinyxml2::XMLElement* data = doc.FirstChildElement("Data");
    if (data != nullptr)
    {
        game = data->FirstChildElement("jeu");
        if (game != nullptr)
        {
            return true;
        }
    }
    return false;
}

std::string ScreenScraperXML::getRomName()
{
    tinyxml2::XMLElement* names = game->FirstChildElement("noms");
    int i = 0;
    std::string romName;
    for (tinyxml2::XMLElement* name = names->FirstChildElement("nom"); name != nullptr;
         name = name->NextSiblingElement("nom"))
    {
        if (i == 0)
        {
            romName = name->GetText();
        }
        const char* rawName = name->Attribute("region");
        if (rawName != nullptr)
        {
            std::string nameStr(rawName);
            if (nameStr == "wor")
            {
                romName = name->GetText();
                break;
            }
        }
        i++;
    }
    return romName;
}

std::string ScreenScraperXML::getPlayers()
{
    tinyxml2::XMLElement* players = game->FirstChildElement("joueurs");
    if (players != nullptr)
    {
        return players->GetText();
    }
    return "1";
}

std::string ScreenScraperXML::getDescription()
{
    tinyxml2::XMLElement* descriptions = game->FirstChildElement("synopsis");
    if (descriptions != nullptr)
    {
        for (tinyxml2::XMLElement* synopsis = descriptions->FirstChildElement("synopsis"); synopsis != nullptr;)
        {
            return synopsis->GetText();
        }
    }
    return "";
}

int ScreenScraperXML::getYear()
{
    tinyxml2::XMLElement* dates = game->FirstChildElement("dates");
    if (dates != nullptr)
    {
        std::string romName;
        for (tinyxml2::XMLElement* date = dates->FirstChildElement("date"); date != nullptr;)
        {
            std::string romYear = date->GetText();
            return std::atoi(romYear.c_str());
        }
    }
    return 0;
}

int ScreenScraperXML::getId()
{
    if (game != nullptr)
    {
        const char* gameId = game->Attribute("id");
        if (gameId != nullptr)
        {
            return std::atoi(gameId);
        }
    }
    return 0;
}

std::string ScreenScraperXML::getGenre()
{
    tinyxml2::XMLElement* genres = game->FirstChildElement("genres");
    if (genres != nullptr)
    {
        for (tinyxml2::XMLElement* genre = genres->FirstChildElement("genre"); genre != nullptr;
             genre = genre->NextSiblingElement("genre"))
        {
            const char* language = genre->Attribute("langue");
            if (language != nullptr)
            {
                std::string langStr(language);
                if (langStr == "en")
                {
                    return genre->GetText();
                }
            }
        }
    }
    return "";
}

std::string ScreenScraperXML::getDeveloper()
{
    tinyxml2::XMLElement* developer = game->FirstChildElement("developpeur");
    if (developer != nullptr)
    {
        return developer->GetText();
    }
    return "";
}

std::string ScreenScraperXML::getConsole()
{
    tinyxml2::XMLElement* console = game->FirstChildElement("systeme");
    if (console != nullptr)
    {
        return console->GetText();
    }
    return "";
}

std::string ScreenScraperXML::getCRC()
{
    tinyxml2::XMLElement* rom = game->FirstChildElement("rom");
    if (rom != nullptr)
    {
        tinyxml2::XMLElement* romCrc = rom->FirstChildElement("romcrc");
        return romCrc->GetText();
    }
    return "";
}

std::string ScreenScraperXML::getSuffix()
{
    tinyxml2::XMLElement* rom = game->FirstChildElement("rom");
    if (rom != nullptr)
    {
        tinyxml2::XMLElement* clonetypes = rom->FirstChildElement("clonetypes");
        if (clonetypes != nullptr)
        {
            tinyxml2::XMLElement* clonetypes_fr = clonetypes->FirstChildElement("clonetypes_fr");
            if (clonetypes_fr != nullptr)
            {
                tinyxml2::XMLElement* clonetype = clonetypes_fr->FirstChildElement("clonetype_fr");
                if (clonetype != nullptr)
                {
                    return clonetype->GetText();
                }
            }
        }
    }
    return std::string();
}