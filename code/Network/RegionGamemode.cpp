#include <kamek.hpp>
#include <PulsarEngine/Settings/Settings.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <VP.hpp>

namespace VP {
namespace Network{
void ResetGamemodeAndTimer(){
    System *vp = System::GetsInstance();
        const GameMode gameMode = RaceData::sInstance->menusScenario.settings.gamemode;
        vp->isRegModeSelected = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE;
        vp->vrScreenTimer = 0;
    }
kmBranch(0x8064a848, ResetGamemodeAndTimer);
} // namespace Network
} // namespace VP