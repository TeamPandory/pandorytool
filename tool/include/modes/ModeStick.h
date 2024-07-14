#pragma once
#include "EditionCheck.h"
#include "ModeJailbreakStick.h"
#include "definitions/Sticks.h"
#include "modes/ModeDXStick.h"
#include "types.h"
#include <string>

class ModeStick
{
  protected:
    std::string& stickType;
    std::string& targetDir;
    EditionCheck editionCheck;
    ModeJailbreakStick modeJailbreakStick;
    ModeDXStick modeDXStick;
    Sticks sticks;

  public:
    ModeStick(std::string& stickType, std::string& targetDir);

    int main();

    int makeStick(const std::string& name);

    int makeStick(const downloadDefinition& stickData);
};