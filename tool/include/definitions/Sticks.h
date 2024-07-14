#pragma once

#include "types.h"
#include <map>

class Sticks
{
  protected:
    std::map<std::string, downloadDefinition> sticks;

  public:
    Sticks();
    downloadDefinition getStickByName(const std::string& name);
};