#include <kamek.hpp>
#include <MarioKartWii/UI/Layout/ControlLoader.hpp>
#include <VP.hpp>

namespace VP {
namespace Race{
void CustomItemWindow(ControlLoader *loader, const char *folderName, const char *ctrName, const char *variant, const char **animNames){
    const System::Gamemode gamemode = System::GetGamemode();
    if (gamemode == System::RACESETTING_MODE_BSS){
        ctrName = "item_window_BSS";
    }
    else if (gamemode == System::RACESETTING_MODE_BBB){
        ctrName = "item_window_BBB";
    }
    else if (gamemode != System::RACESETTING_MODE_NONE){
        ctrName = "item_window_NOR";
    }
    else{
        ctrName = "item_window_new";
    }
    loader->Load(folderName, ctrName, variant, animNames);
}
kmCall(0x807ef50c, CustomItemWindow);

void CustomItemBalloon(ControlLoader *loader, const char *folderName, const char *ctrName, const char *variant, const char **animNames){
    const System::Gamemode gamemode = System::GetGamemode();
    if (gamemode != System::RACESETTING_MODE_NONE){
        ctrName = "chase_iNOR"; // I still want default icons for the ItemBalloon even in other gamemodes, but custom icons in the ItemWindow.
    }
    else{
        ctrName = "chase_icon";
    }
    loader->Load(folderName, ctrName, variant, animNames);
}
kmCall(0x807f2064, CustomItemBalloon);
} // namespace Race
} // namespace VP