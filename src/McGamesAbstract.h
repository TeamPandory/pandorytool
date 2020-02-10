#ifndef PANDORY_MCGAMESABSTRACT_H
#define PANDORY_MCGAMESABSTRACT_H

#include <string>

class McGamesAbstract {
protected:
    std::string emulatorName;
	std::string emulatorLoad;
    std::string romName;
    std::string romFileName;
    std::string romDescription;
    std::string language;
    int year;
    std::string players;
    std::string romDeveloper;
    std::string romPath;
    bool saveState;

public:
    virtual void generate(std::string filename) = 0;
    void setLanguage(const std::string &language);
    void setYear(int year);
    void setPlayers(const std::string &players);
    void setRomPath(const std::string &romPath);
    void setRomDeveloper(const std::string &romDeveloper);
    void setEmulatorName(const std::string &emulatorName);
	void setEmulatorLoad(const std::string &emulatorLoad);
    void setRomFileName(const std::string &romFileName);
    void setRomName(const std::string &romName);
    void setRomDescription(const std::string &romDescription);
    void setSaveState(bool saveState);
};


#endif //PANDORY_MCGAMESABSTRACT_H
