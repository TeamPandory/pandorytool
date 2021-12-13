#ifndef PANDORY_DXPATCHES_H
#define PANDORY_DXPATCHES_H

#include <string>
#include <vector>
#include "../Fs.h"
#include "../Hash.h"

class DXPatches {
protected:
    Hash hash;
    std::string getOriginalHash(const std::string& file);

    std::vector<std::string> validHashes =
    {
        std::string("FD4264BC92F1839E3A85E1ECDA00526B"),
        std::string("E66949629A5D2637C4ED682765584C99"),
        std::string("DAEFC008E8A2629778131C7190C70B38"),
        std::string("C33947D5980D9753190909543D48A974"),
        std::string("AFD1442815D3B93F3721B4D97EAE31C4"),
        std::string("AC7D1BD514CBD4F4B6A7559E08189693"),
        std::string("6205806AF22FDD40150E14EC5ACA2A8F"),
        std::string("95F47E5172B07E86D47060325F7E9507"),
        std::string("34A2F2CAF9DE3B79541B7D22795213F7"),
        std::string("9EB812D6530E13113418122F7670ABA7"),
        std::string("8B52524CAC994866B36083BE460741DA"),
        std::string("7DEF0E6CB22B743962FCB50F0333D5C6"),
        std::string("EF1A6C45D8E31C8D203E4D790E8722E8"), //dxsagaplus hadc
        std::string("85180B4195A9BE494E80816E39434EB0"), //dxsagaplus rade
        std::string("2D1B365539F6BD63ED85BCE6EBE493F7"), //1.4 rade
        std::string("9EB812D6530E13113418122F7670ABA7"), //dx special 1.4 hadc jamma
        std::string("D5E3386A978CBF7E67C582896138213E"), //dx special 1.4 rade jamma

    };

public:
    bool isValidZip(std::string &zipPrefix);
};
#endif //PANDORY_DXPATCHES_H

