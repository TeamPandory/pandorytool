#pragma once
#include "McGamesAbstract.h"
#include <string>

class McGamesXML : public McGamesAbstract
{
  public:
    void generate(std::string filename) override;
};