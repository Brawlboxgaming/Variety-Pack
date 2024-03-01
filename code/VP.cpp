#include <MarioKartWii/Race/RaceData.hpp>
#include <PulsarEngine/SlotExpansion/CupsConfig.hpp>
#include <PulsarEngine/Settings/UI/SettingsPanel.hpp>
#include <VP.hpp>

namespace VP {
Pulsar::System *System::Create() {
    return new System(); //now Pulsar::sInstance is of type VP
}
Pulsar::System::Inherit CreateVP(System::Create); //Create a Inherit that'll get called back by Pulsar::CreatePulsar

void System::AfterInit(){
    // Create new settings page (by incrementing pageCount)
    ++Pulsar::UI::SettingsPanel::pageCount;

    // Radio button count for new page
    Pulsar::UI::SettingsPanel::radioButtonCount[SETTINGSTYPE_VP] = 1;
    // No Music Option Count i.e. Disabled/Enabled
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[SETTINGSTYPE_VP][0] = 2;

    // Scroller count for new page
    Pulsar::UI::SettingsPanel::scrollerCount[SETTINGSTYPE_VP] = 1;
    // Gamemode Scroller Option Count
    Pulsar::UI::SettingsPanel::optionsPerPagePerScroller[SETTINGSTYPE_VP][0] = 4;

    // Create settings for existing pages
    // Restrict Kart Selection + Character Selection in Friend Rooms
    Pulsar::UI::SettingsPanel::radioButtonCount[Pulsar::Settings::SETTINGSTYPE_HOST] = 5;
    // Restrict Kart Selection Count i.e. Default/Karts/Bikes
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[Pulsar::Settings::SETTINGSTYPE_HOST][3] = 3;
    // Restrict Character Selection Count i.e. Default/Light/Medium/Heavy
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[Pulsar::Settings::SETTINGSTYPE_HOST][4] = 4;
}

WeightClass System::GetWeightClass(const CharacterId id){
    switch (id)
    {
        case BABY_MARIO:
        case BABY_LUIGI:
        case BABY_PEACH:
        case BABY_DAISY:
        case TOAD:
        case TOADETTE:
        case KOOPA_TROOPA:
        case DRY_BONES:
            return LIGHTWEIGHT;
        case MARIO:
        case LUIGI:
        case PEACH:
        case DAISY:
        case YOSHI:
        case BIRDO:
        case DIDDY_KONG:
        case BOWSER_JR:
            return MEDIUMWEIGHT;
        case WARIO:
        case WALUIGI:
        case DONKEY_KONG:
        case BOWSER:
        case KING_BOO:
        case ROSALINA:
        case FUNKY_KONG:
        case DRY_BOWSER:
            return HEAVYWEIGHT;
        default:
            return MIIS;
    }
}

CharacterRestriction System::GetCharacterRestriction(){
    const GameMode gameMode = RaceData::sInstance->menusScenario.settings.gamemode;
    const bool isFroom = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE;
    if (isFroom){
        return GetsInstance()->charRestrictMode;
    }
    return CHAR_DEFAULTSELECTION;
}

KartRestriction System::GetKartRestriction(){
    const GameMode gameMode = RaceData::sInstance->menusScenario.settings.gamemode;
    const bool isFroom = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE;
    if (isFroom){
        return GetsInstance()->kartRestrictMode;
    }
    return KART_DEFAULTSELECTION;
}

Gamemode System::GetGamemode(){
    const bool isRegs = Pulsar::CupsConfig::IsRegsSituation();
    const GameMode gameMode = RaceData::sInstance->racesScenario.settings.gamemode;
    const bool isTTs = gameMode == MODE_TIME_TRIAL;
    const bool isFroom = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE;
    if (!isRegs){
        if (!isTTs){
            if (isFroom){
                return GetsInstance()->hostMode;
            }
            return static_cast<Gamemode>(Pulsar::Settings::Mgr::GetSettingValue(static_cast<Pulsar::Settings::Type>(SETTINGSTYPE_VP), SETTINGVP_SCROLLER_MODE));
        }
        return RACESETTING_MODE_NORMAL;
    }
    return RACESETTING_MODE_NONE;
}
} // namespace VP