#pragma once
#include <ostream>
#include <string>

class SystemDefinition
{
  public:
    SystemDefinition();
    SystemDefinition(int type, int loadTime, std::string systemName, std::string colour, bool saveState,
                     bool renameFlag);

  protected:
    int type = 0;
    int loadTime = 0;
    std::string systemName;
    std::string colour;
    bool saveState = true;
    bool renameFlag = true;

  public:
    int getId() const;
    int getLoadTime() const;
    const std::string& getSystemName() const;
    const std::string& getColour() const;
    bool isSaveState() const;
    bool isRenameFlag() const;
};