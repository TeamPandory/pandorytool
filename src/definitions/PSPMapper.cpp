#include <string>
#include "PSPMapper.h"

PSPMapper::PSPMapper() {
    stockGames["tk6"] = {6,1,2};
    stockGames["TK5"] = {6,1,2};
    stockGames["MortalKombat"] = {6,1,2};
    stockGames["SoulEater"] = {6,1,2};
    stockGames["Weekly"] = {6,1,2};
    stockGames["WWEAllStar"] = {6,1,2};
    stockGames["KidouSenshiGundam"] = {6,1,1};
    stockGames["NarutoShippuuden"] = {0,5,1};
    stockGames["Daxter"] = {0,5,1};
    stockGames["CangYiMSL2"] = {6,1,2};
    stockGames["NBA06"] = {0,1,1};
    stockGames["RidgeRacer2"] = {2,5,1};
    stockGames["HeatSeeker"] = {6,2,1};
    stockGames["InitialD"] = {2,1,1};
    stockGames["GTCar"] = {2,1,1};
    stockGames["wipeout"] = {5,2,1};
    stockGames["JiaTingJS"] = {6,1,1};
    stockGames["MouFaSNNY"] = {6,1,1};
    stockGames["taoguiZ"] = {0,1,1};
    stockGames["WuShuangDS"] = {0,1,1};
    stockGames["zs5"] = {0,1,1};
    stockGames["GuiltyGear"] = {6,3,2};
    stockGames["FateUnlimitedCode"] = {6,5,1};
    stockGames["SoulcaliburBrokenDestiny"] = {6,1,1};
    stockGames["PowerStoneCollection"] = {6,5,1};
    stockGames["StreetFighterAlpha3Max"] = {0,4,2};
    stockGames["DragonBallZ"] = {6,4,1};
    stockGames["bleach"] = {0,2,1};
    stockGames["PacManWorld3"] = {0,1,1};
    stockGames["MegaManX"] = {0,5,1};
    stockGames["LocoRoco"] = {3,1,1};
    stockGames["AuditionPortable"] = {6,1,1};
    stockGames["Luxor"] = {0,1,1};
    stockGames["Numpla10000Mon"] = {6,1,1};
    stockGames["7wonders"] = {6,4,1};
    stockGames["Numblast"] = {6,1,1};
    stockGames["FinalFantasy"] = {0,2,1};
    stockGames["CiKeXT"] = {0,2,1};
    stockGames["pes2012"] = {0,2,4};
    stockGames["gwlrP3"] = {0,2,1};
}

const std::map<std::string, pspConfigGameDef> &PSPMapper::getStockGames() const {
    return stockGames;
}
