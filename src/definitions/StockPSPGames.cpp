#include <string>
#include <map>

struct pspGameDef {
    int controlType = 0;
    int ppssppSettings = 0;
    int players = 0;
};

int junk() {
    std::map<std::string, pspGameDef> stockGames;
    stockGames["tk6"] = {0,1,2};
    stockGames["TK5"] = {0,1,2};
    stockGames["MortalKombat"] = {0,1,1};
    stockGames["SoulEater"] = {0,1,1};
    stockGames["Weekly"] = {0,1,1};
    stockGames["WWEAllStar"] = {0,1,1};
    stockGames["KidouSenshiGundam"] = {0,1,1};
    stockGames["NarutoShippuuden"] = {0,1,1};
    stockGames["Daxter"] = {0,1,1};
    stockGames["CangYiMSL2"] = {0,1,1};
    stockGames["NBA06"] = {0,1,1};
    stockGames["RidgeRacer2"] = {2,1,1};
    stockGames["HeatSeeker"] = {0,1,1};
    stockGames["InitialD"] = {0,1,1};
    stockGames["GTCar"] = {0,1,1};
    stockGames["wipeout"] = {0,1,1};
    stockGames["JiaTingJS"] = {0,1,1};
    stockGames["MouFaSNNY"] = {0,1,1};
    stockGames["taoguiZ"] = {0,1,1};
    stockGames["WuShuangDS"] = {0,1,1};
    stockGames["zs5"] = {0,1,1};
    stockGames["GuiltyGear"] = {0,1,1};
    stockGames["FateUnlimitedCode"] = {0,1,1};
    stockGames["SoulcaliburBrokenDestiny"] = {0,1,1};
    stockGames["PowerStoneCollection"] = {0,1,1};
    stockGames["StreetFighterAlpha3Max"] = {0,1,1};
    stockGames["DragonBallZ"] = {0,1,1};
    stockGames["bleach"] = {0,1,1};
    stockGames["PacManWorld3"] = {0,1,1};
    stockGames["MegaManX"] = {0,1,1};
    stockGames["LocoRoco"] = {1,1,1};
    stockGames["AuditionPortable"] = {0,1,1};
    stockGames["Luxor"] = {0,1,1};
    stockGames["Numpla10000Mon"] = {0,1,1};
    stockGames["7wonders"] = {0,1,1};
    stockGames["Numblast"] = {0,1,1};
}
