#include <kamek.hpp>
#include <game/UI/Layout/ControlLoader.hpp>
#include <VP.hpp>

void CustomItemWindow(ControlLoader *loader, const char *folderName, const char *ctrName, const char *variant, const char **animNames){
    const VP::Gamemode gamemode = VP::GetGamemode();
    if (gamemode == VP::RACESETTING_MODE_BSS){
        ctrName = "item_window_BSS";
    }
    else if (gamemode == VP::RACESETTING_MODE_BBB){
        ctrName = "item_window_BBB";
    }
    else if (gamemode != VP::RACESETTING_MODE_NONE){
        ctrName = "item_window_NOR";
    }
    loader->Load(folderName, ctrName, variant, animNames);
}
kmCall(0x807ef50c, CustomItemWindow);

void CustomItemBalloon(ControlLoader *loader, const char *folderName, const char *ctrName, const char *variant, const char **animNames){
    const VP::Gamemode gamemode = VP::GetGamemode();
    if (gamemode != VP::RACESETTING_MODE_NONE){
        ctrName = "chase_iNOR";
    }
    loader->Load(folderName, ctrName, variant, animNames);
}
kmCall(0x807f2064, CustomItemBalloon);