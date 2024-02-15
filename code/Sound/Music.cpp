#include <VP.hpp>

namespace VP {
namespace Sound {
    void SetMusicState(){
        SoundPlayersVolumeMgr::sInstance->volumes[0].curValue = 1;
        if (Pulsar::Settings::Mgr::GetSettingValue(Pulsar::Settings::SETTINGSTYPE_MENU, System::SETTINGMENU_RADIO_MUSIC)){
            SoundPlayersVolumeMgr::sInstance->volumes[0].curValue = 0;
        }
    }
    kmBranch(0x80710ba8, SetMusicState);
    kmBranch(0x80715c38, SetMusicState);
    kmBranch(0x80715e60, SetMusicState);
    Pulsar::Settings::Hook PatchMusicInstantly(SetMusicState);
} // namespace Sound 
} // namespace VP