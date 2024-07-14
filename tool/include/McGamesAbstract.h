#pragma once
#include <string>

class McGamesAbstract
{
  protected:
    std::string emulatorId;
    std::string emulatorLoad;
    std::string romTitle;
    std::string romTitleSuffix;

  public:
    void setRomTitleSuffix(const std::string& romTitleSuffix);

  protected:
    std::string romShortId;
    std::string romFileName;
    std::string romDescription;
    std::string console;
    std::string language;
    std::string additionalRomName;
    std::string fileHash;

    int genre;
    int year;
    std::string players;
    std::string romDeveloper;
    bool saveState;

  public:
    virtual void generate(std::string filename) = 0;
    void setLanguage(const std::string& language);
    void setYear(int year);
    void setGenre(int genre);
    void setPlayers(const std::string& numberOfPlayers);
    void setRomDeveloper(const std::string& developerName);
    void setEmulatorId(const std::string& emulatorName);
    void setEmulatorLoad(const std::string& emulatorLoad);
    void setRomShortId(const std::string& romFileName);
    void setRomTitle(const std::string& title);
    void setRomFileName(const std::string& filename);
    void setRomDescription(const std::string& romDescription);
    void setFileHash(const std::string& fileCrc);
    void setSaveState(bool saveStateStatus);
    void addAdditionalRom(std::string& additionalRomNames);
    std::string getFileHash();
    std::string getRomTitle();
    bool isSaveState() const;
    void setConsole(const std::string& consoleName);
    std::string getConsole();

    int getYear() const;

    const std::string& getRomTitleSuffix() const;
};