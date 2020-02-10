#ifndef PANDORY_MCGAMESABSTRACT_H
#define PANDORY_MCGAMESABSTRACT_H

#include <string>

class McGamesAbstract {
protected:
    std::string emulatorId;
	std::string emulatorLoad;
    std::string romFullName;
    std::string romShortId;
    std::string romFileName;
    std::string romDescription;
    std::string language;
    int year;
    std::string players;
    std::string romDeveloper;
    std::string romDirectory;
    bool saveState;

public:
    virtual void generate(std::string filename) = 0;
    void setLanguage(const std::string &language);
    void setYear(int year);
    void setPlayers(const std::string &players);
    void setRomPath(const std::string &romPath);
    void setRomDeveloper(const std::string &romDeveloper);
    void setEmulatorId(const std::string &emulatorName);
	void setEmulatorLoad(const std::string &emulatorLoad);
    void setRomShortId(const std::string &romFileName);
    void setRomTitle(const std::string &romTitle);
    void setRomFileName(const std::string &romFileName);
    void setRomDescription(const std::string &romDescription);
    void setSaveState(bool saveState);
};


#endif //PANDORY_MCGAMESABSTRACT_H
