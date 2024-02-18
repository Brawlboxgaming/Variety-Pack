#include <VP.hpp>

namespace VP {
namespace Sound {
    void SetMusicState(){
        SoundPlayersVolumeMgr::sInstance->volumes[0].curValue = 1;
        if (Pulsar::Settings::Mgr::GetSettingValue(static_cast<Pulsar::Settings::Type>(System::SETTINGSTYPE_VP), System::SETTINGVP_RADIO_MUSIC)){
            SoundPlayersVolumeMgr::sInstance->volumes[0].curValue = 0;
        }
    }
    kmBranch(0x80710ba8, SetMusicState);
    kmBranch(0x80715c38, SetMusicState);
    kmBranch(0x80715e60, SetMusicState);
    kmBranch(0x8070f598, SetMusicState);
    Pulsar::Settings::Hook PatchMusicInstantly(SetMusicState);
} // namespace Sound 
} // namespace VP