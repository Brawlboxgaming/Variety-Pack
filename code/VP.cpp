#include <MarioKartWii/Race/RaceData.hpp>
#include <PulsarEngine/SlotExpansion/CupsDef.hpp>
#include <PulsarEngine/Settings/UI/SettingsPanel.hpp>
#include <VP.hpp>

namespace VP {
Pulsar::System *System::Create() {
    return new System(); //now Pulsar::sInstance is of type VP
}
Pulsar::System::Inherit CreateVP(System::Create); //Create a Inherit that'll get called back by Pulsar::CreatePulsar

void System::AfterInit(){
    ++Pulsar::UI::SettingsPanel::scrollerCount[Pulsar::Settings::SETTINGSTYPE_RACE];
    Pulsar::UI::SettingsPanel::optionsPerPagePerScroller[Pulsar::Settings::SETTINGSTYPE_RACE][0] = 4;
}

System::Gamemode System::GetGamemode(){
    const bool isRegs = Pulsar::CupsConfig::IsRegsSituation();
    const GameMode gameMode = RaceData::sInstance->racesScenario.settings.gamemode;
    const bool isTTs = gameMode == MODE_TIME_TRIAL;
    const bool isFroom = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE;
    if (!isRegs){
        if (!isTTs){
            if (isFroom){
                return System::GetsInstance()->hostMode;
            }
            return static_cast<Gamemode>(Pulsar::Settings::Mgr::GetSettingValue(Pulsar::Settings::SETTINGSTYPE_RACE, SETTINGRACE_SCROLLER_MODE));
        }
        return RACESETTING_MODE_NORMAL;
    }
    return RACESETTING_MODE_NONE;
}
} // namespace VP