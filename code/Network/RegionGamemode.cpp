#include <kamek.hpp>
#include <PulsarEngine/Settings/Settings.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <VP.hpp>

namespace VP {
namespace Network{
void ResetGamemodeAndTimer(){
    System *vp = System::GetsInstance();
        //vp->isRegModeSelected = false;
        vp->vrScreenTimer = 0;
    }
kmBranch(0x8064a848, ResetGamemodeAndTimer);
} // namespace Network
} // namespace VP