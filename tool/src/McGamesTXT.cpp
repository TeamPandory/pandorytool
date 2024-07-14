#include "McGamesTXT.h"
#include <fstream>

void McGamesTXT::generate(std::string filename)
{
    std::ofstream fp;
    fp.open(filename);
    fp << "display_name\t" << romShortId << std::endl;
    fp << "loading_time\t" << emulatorLoad << std::endl;
    fp << "emulator_type\t" << emulatorId << std::endl;
    fp << "genre\t" << genre << std::endl;
    fp << "production\t"
       << "" << std::endl;
    fp << "year\t" << year << std::endl;
    fp << "support_xbr\t"
       << "0" << std::endl;
    fp.close();
}
