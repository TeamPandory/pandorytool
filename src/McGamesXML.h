#ifndef PANDORY_MCGAMESXML_H
#define PANDORY_MCGAMESXML_H

#include <string>
#include "McGamesAbstract.h"

class McGamesXML : public McGamesAbstract {
public:
    void generate(std::string filename) override;

};


#endif //PANDORY_MCGAMESXML_H
