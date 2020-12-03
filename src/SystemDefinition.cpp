#include "SystemDefinition.h"

#include <utility>


SystemDefinition::SystemDefinition(int type, int loadTime, std::string systemName, std::string colour,
                                   bool saveState, bool renameFlag) : type(type), loadTime(loadTime),
                                                                      systemName(std::move(systemName)), colour(std::move(colour)),
                                                                      saveState(saveState), renameFlag(renameFlag) {}

SystemDefinition::SystemDefinition() {

}

int SystemDefinition::getId() const {
    return type;
}

int SystemDefinition::getLoadTime() const {
    return loadTime;
}

const std::string &SystemDefinition::getSystemName() const {
    return systemName;
}

const std::string &SystemDefinition::getColour() const {
    return colour;
}

bool SystemDefinition::isSaveState() const {
    return saveState;
}

bool SystemDefinition::isRenameFlag() const {
    return renameFlag;
}
