#pragma once
#include "types.h"
#include <string>

class StickExtractor
{
  public:
    int exractToFolder(const downloadDefinition& stick, std::string& tarPath, std::string& targetFolder);
};