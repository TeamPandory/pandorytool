#pragma once
#include "McGamesAbstract.h"
#include <string>

class McGamesTXT : public McGamesAbstract
{
  public:
    void generate(std::string filename) override;
};