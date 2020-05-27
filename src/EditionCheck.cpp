#include "EditionCheck.h"

bool EditionCheck::isShareware() {
#ifdef NO_SHAREWARE_LIMIT
    return false;
#else
    return true;
#endif
}

bool EditionCheck::isUltimate() {
    return !isShareware();
}
