#include <VP.hpp>

namespace VP {
Pulsar::System *System::Create() {
    return new System(); //now Pulsar::sInstance is of type VP
}
Pulsar::System::Inherit CreateVP(System::Create); //Create a Inherit that'll get called back by Pulsar::CreatePulsar

void System::AfterInit(){
    ++Pulsar::UI::SettingsPanel::pageCount;

    // Radio button count for new page
    Pulsar::UI::SettingsPanel::radioButtonCount[SETTINGSTYPE_VP] = 3;
    // Restrict Kart Selection Count i.e. Default/Karts/Bikes
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[SETTINGSTYPE_VP][0] = 3;
    // Restrict Character Selection Count i.e. Default/Light/Medium/Heavy
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[SETTINGSTYPE_VP][1] = 4;
    // Force Transmission in friend rooms
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[SETTINGSTYPE_VP][2] = 3;

    // Scroller count for new page
    Pulsar::UI::SettingsPanel::scrollerCount[SETTINGSTYPE_VP] = 1;
    // Gamemode Scroller Option Count
    Pulsar::UI::SettingsPanel::optionsPerPagePerScroller[SETTINGSTYPE_VP][0] = 4;
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

u8 System::GetTransmission(){
    const GameMode gameMode = RaceData::sInstance->menusScenario.settings.gamemode;
    const bool isFroom = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE;
    if (isFroom){
        return GetsInstance()->forcedTransmission;
    }
    return TRANSMISSION_DEFAULT;
}

Gamemode System::GetGamemode(){
    const bool isRegs = Pulsar::CupsConfig::IsRegsSituation();
    const GameMode gameMode = RaceData::sInstance->racesScenario.settings.gamemode;
    const GameMode menuGameMode = RaceData::sInstance->menusScenario.settings.gamemode;
    const bool isTTs = gameMode == MODE_TIME_TRIAL || menuGameMode == MODE_TIME_TRIAL;
    const bool isFroom = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE || menuGameMode == MODE_PRIVATE_VS || menuGameMode == MODE_PRIVATE_BATTLE;
    const bool isRegional = gameMode == MODE_PUBLIC_VS || gameMode == MODE_PUBLIC_BATTLE || menuGameMode == MODE_PUBLIC_VS || menuGameMode == MODE_PUBLIC_BATTLE;
    if (!isRegs){
        if (!isTTs && !isRegional){
            if (isFroom){
                return GetsInstance()->hostMode;
            }
            return static_cast<Gamemode>(Pulsar::Settings::Mgr::GetSettingValue(static_cast<Pulsar::Settings::Type>(SETTINGSTYPE_VP), SETTINGVP_SCROLLER_MODE));
        }
        return GAMEMODE_NORMAL;
    }
    return GAMEMODE_NONE;
}

void UpdateVRBMGText(Pages::VR *page){ //assume it's of this type so we can use it's members
    if (page->pageId == PAGE_VR && !Pulsar::CupsConfig::IsRegsSituation()){
        const GameMode gameMode = RaceData::sInstance->menusScenario.settings.gamemode;
        const bool isFroom = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE;
        System *vp = System::GetsInstance();
        if (isFroom && vp->forcedTransmission != TRANSMISSION_DEFAULT){
            if (vp->vrScreenTimer == 0){
                SectionMgr* sectionMgr = SectionMgr::sInstance;
                Pages::CountDownTimer* countdownTimer = sectionMgr->curSection->Get<Pages::CountDownTimer>();
                page->ctrlMenuBottomMessage.SetMessage(countdownTimer->GetInstructionBmgId());
                vp->vrScreenTimer = 360;
            }
            else if(vp->vrScreenTimer == 240){
                page->ctrlMenuBottomMessage.SetMessage(DISPLAY_GAMEMODE_NORMAL + vp->GetGamemode());
            }
            else if(vp->vrScreenTimer == 120){
                page->ctrlMenuBottomMessage.SetMessage(DISPLAY_FORCEDTRANS_OUTSIDE + vp->forcedTransmission - 1);
            }
        }
        else{ 
            if (vp->vrScreenTimer == 0){
                SectionMgr* sectionMgr = SectionMgr::sInstance;
                Pages::CountDownTimer* countdownTimer = sectionMgr->curSection->Get<Pages::CountDownTimer>();
                page->ctrlMenuBottomMessage.SetMessage(countdownTimer->GetInstructionBmgId());
                vp->vrScreenTimer = 240;
            }
            else if(vp->vrScreenTimer == 120){
                page->ctrlMenuBottomMessage.SetMessage(DISPLAY_GAMEMODE_NORMAL + vp->GetGamemode());
            }
        }
        --vp->vrScreenTimer;
    }
}
kmBranch(0x805bb22c, UpdateVRBMGText);
} // namespace VP