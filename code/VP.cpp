#include <game/Race/RaceData.hpp>
#include <Pulsar/SlotExpansion/CupsDef.hpp>
#include <Pulsar/Settings/UI/SettingsPanel.hpp>
#include <VP.hpp>

Pulsar::System *VP::Create() {
    return new VP(); //now Pulsar::sInstance is of type VP
}
Pulsar::System::Inherit CreateVP(VP::Create); //Create a Inherit that'll get called back by Pulsar::CreatePulsar

void VP::AfterInit(){
    ++Pulsar::UI::SettingsPanel::scrollerCount[Pulsar::Settings::SETTINGSTYPE_RACE];
    Pulsar::UI::SettingsPanel::optionsPerPagePerScroller[Pulsar::Settings::SETTINGSTYPE_RACE][0] = 4;
}

VP::Gamemode VP::GetGamemode(){
    const bool isRegs = Pulsar::CupsConfig::IsRegsSituation();
    const GameMode gameMode = RaceData::sInstance->racesScenario.settings.gamemode;
    const bool isTTs = gameMode == MODE_TIME_TRIAL;
    const bool isFroom = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE;
    if (!isRegs){
        if (!isTTs){
            if (isFroom){
                return VP::GetsInstance()->hostMode;
            }
            return static_cast<Gamemode>(Pulsar::Settings::Mgr::GetSettingValue(Pulsar::Settings::SETTINGSTYPE_RACE, SETTINGRACE_SCROLLER_MODE));
        }
        return RACESETTING_MODE_NORMAL;
    }
    return RACESETTING_MODE_NONE;
}