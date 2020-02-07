#ifndef PANDORY_MCGAMESXML_H
#define PANDORY_MCGAMESXML_H

#include <string>

class McGamesXML {
protected:
    std::string emulatorName;
    std::string romName;
    std::string romDescription;
    std::string language;
    int year;
    std::string romDeveloper;
    std::string romPath;

public:
    void generate(std::string xmlFilename);
    void setEmulatorName(const std::string &emulatorName);

    void setRomName(const std::string &romName);

    void setRomDescription(const std::string &romDescription);

    void setLanguage(const std::string &language);

    void setYear(int year);

    void setRomDeveloper(const std::string &romDeveloper);

    void setRomPath(const std::string &romPath);
};


#endif //PANDORY_MCGAMESXML_H
