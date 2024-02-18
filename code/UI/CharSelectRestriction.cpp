#include <VP.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuCharacterSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/CharacterSelect.hpp>

namespace VP {
namespace UI {
    System::WeightClass GetMiiWeightClass(CtrlMenuCharacterSelect &charSelect){
        CharacterId CheckOrder[6] = {
            MII_S_A_MALE,
            MII_S_A_FEMALE,
            MII_M_A_MALE,
            MII_M_A_FEMALE,
            MII_L_A_MALE,
            MII_L_A_FEMALE
        };
        CtrlMenuCharacterSelect::ButtonDriver *miiButton = 0;
        u8 ix = 0;
        while(miiButton == 0 && ix < 6){
            miiButton = charSelect.GetButtonDriver(CheckOrder[ix]);
            ++ix;
        }
        if (ix < 2){
            return System::LIGHTWEIGHT;
        }
        else if(ix < 4){
            return System::MEDIUMWEIGHT;
        }
        return System::HEAVYWEIGHT;
    }
    
    CtrlMenuCharacterSelect::ButtonDriver *GetMiiButtonDriver(CtrlMenuCharacterSelect &charSelect, System::CharacterRestriction rest, bool altOutfit){
        CharacterId CheckOrder[4];
        if (rest == System::CHAR_LIGHTONLY){
            CheckOrder[0] = MII_M_A_MALE;
            CheckOrder[1] = MII_M_A_FEMALE;
            CheckOrder[2] = MII_L_A_MALE;
            CheckOrder[3] = MII_L_A_FEMALE;
            if (altOutfit){
                CheckOrder[0] = MII_M_B_MALE;
                CheckOrder[1] = MII_M_B_FEMALE;
                CheckOrder[2] = MII_L_B_MALE;
                CheckOrder[3] = MII_L_B_FEMALE;
            }
        }
        else if (rest == System::CHAR_MEDIUMONLY){
            CheckOrder[0] = MII_S_A_MALE;
            CheckOrder[1] = MII_S_A_FEMALE;
            CheckOrder[2] = MII_L_A_MALE;
            CheckOrder[3] = MII_L_A_FEMALE;
            if (altOutfit){
                CheckOrder[0] = MII_S_B_MALE;
                CheckOrder[1] = MII_S_B_FEMALE;
                CheckOrder[2] = MII_L_B_MALE;
                CheckOrder[3] = MII_L_B_FEMALE;
            }
        }
        else{
            CheckOrder[0] = MII_S_A_MALE;
            CheckOrder[1] = MII_S_A_FEMALE;
            CheckOrder[2] = MII_M_A_MALE;
            CheckOrder[3] = MII_M_A_FEMALE;
            if (altOutfit){
                CheckOrder[0] = MII_S_B_MALE;
                CheckOrder[1] = MII_S_B_FEMALE;
                CheckOrder[2] = MII_M_B_MALE;
                CheckOrder[3] = MII_M_B_FEMALE;
            }
        }
        CtrlMenuCharacterSelect::ButtonDriver *miiButton = 0;
        u8 ix = 0;
        while(miiButton == 0 && ix < 4){
            miiButton = charSelect.GetButtonDriver(CheckOrder[ix]);
            ++ix;
        }
        return miiButton;
    }

    void EnableButtons(CtrlMenuCharacterSelect &charSelect){
        for (u8 i = 0; i < 42; i++)
        {
            CtrlMenuCharacterSelect::ButtonDriver *buttonDriver = charSelect.GetButtonDriver(static_cast<CharacterId>(i));
            if (buttonDriver != 0){
                buttonDriver->SetPicturePane("chara", GetCharacterIconPaneName(static_cast<CharacterId>(i)));
                buttonDriver->SetPicturePane("chara_shadow", GetCharacterIconPaneName(static_cast<CharacterId>(i)));
                buttonDriver->SetPicturePane("chara_light_01", GetCharacterIconPaneName(static_cast<CharacterId>(i)));
                buttonDriver->SetPicturePane("chara_light_02", GetCharacterIconPaneName(static_cast<CharacterId>(i)));
                buttonDriver->SetPicturePane("chara_c_down", GetCharacterIconPaneName(static_cast<CharacterId>(i)));
                buttonDriver->manipulator.inaccessible = false;
            }
        }
        
    }

    void DisableButton(CtrlMenuCharacterSelect::ButtonDriver *button){
        button->SetPicturePane("chara", "cha_26_hatena");
        button->SetPicturePane("chara_shadow", "cha_26_hatena");
        button->SetPicturePane("chara_light_01", "cha_26_hatena");
        button->SetPicturePane("chara_light_02", "cha_26_hatena");
        button->SetPicturePane("chara_c_down", "cha_26_hatena");

        button->manipulator.inaccessible = true;
    }

    void RestrictCharacterSelection(PushButton *button, u32 hudSlotId){
        Pages::CharacterSelect *page = SectionMgr::sInstance->curSection->Get<Pages::CharacterSelect>();
        CtrlMenuCharacterSelect &charSelect = page->ctrlMenuCharSelect;
        SectionId curSection = SectionMgr::sInstance->curSection->sectionId;
        System::CharacterRestriction charRestrict = System::GetCharacterRestriction();
        CtrlMenuCharacterSelect::ButtonDriver *driverButtons = charSelect.driverButtonsArray;
        CharacterId currentChar = page->models[hudSlotId].curCharacter;
        System::WeightClass weight = System::GetWeightClass(currentChar);
        CtrlMenuCharacterSelect::ButtonDriver *newButton = charSelect.GetButtonDriver(currentChar);

        EnableButtons(charSelect);

        if (charRestrict != System::CHAR_DEFAULTSELECTION){
            for (int i = System::BUTTON_BABY_MARIO; i < System::BUTTON_MII_A; i++)
            {
                driverButtons[i].manipulator.inaccessible = false;
                if (charRestrict == System::CHAR_LIGHTONLY &&
                i >= System::BUTTON_MARIO && i < System::BUTTON_MII_A){
                    DisableButton(&driverButtons[i]);
                }
                if (charRestrict == System::CHAR_MEDIUMONLY &&
                ((i >= System::BUTTON_BABY_MARIO && i < System::BUTTON_MARIO) || (i >= System::BUTTON_WARIO && i < System::BUTTON_MII_A))){
                    DisableButton(&driverButtons[i]);
                }
                if (charRestrict == System::CHAR_HEAVYONLY &&
                i >= System::BUTTON_BABY_MARIO && i < System::BUTTON_WARIO){
                    DisableButton(&driverButtons[i]);
                }
            }

            if (curSection == SECTION_P2_WIFI ||\
            curSection == SECTION_P2_WIFI_FROOM_VS_VOTING ||
            curSection == SECTION_P2_WIFI_FROOM_TEAMVS_VOTING ||
            curSection == SECTION_P2_WIFI_FROOM_BALLOON_VOTING ||
            curSection == SECTION_P2_WIFI_FROOM_COIN_VOTING){
                DisableButton(&driverButtons[System::BUTTON_MII_A]);
                DisableButton(&driverButtons[System::BUTTON_MII_B]);
            }
            else{
                CtrlMenuCharacterSelect::ButtonDriver *button = GetMiiButtonDriver(charSelect, charRestrict, false);
                if (button != 0) DisableButton(button);
                button = GetMiiButtonDriver(charSelect, charRestrict, true);
                if (button != 0) DisableButton(button);
            }
            if (charRestrict == System::CHAR_LIGHTONLY &&
            (weight != System::LIGHTWEIGHT ||
            ((GetMiiWeightClass(charSelect) != System::LIGHTWEIGHT || RaceData::sInstance->menusScenario.localPlayerCount > 1) &&
            currentChar >= MII_S_A_MALE))){
                newButton->HandleDeselect(hudSlotId, -1);
                if (hudSlotId == 0) newButton = charSelect.GetButtonDriver(static_cast<CharacterId>(BABY_MARIO));
                else if (hudSlotId == 1) newButton = charSelect.GetButtonDriver(static_cast<CharacterId>(BABY_LUIGI));
                newButton->SelectInitialButton(hudSlotId);
                newButton->SetButtonColours(hudSlotId);
                page->OnButtonDriverSelect(newButton, newButton->buttonId, hudSlotId);
            }
            else if (charRestrict == System::CHAR_MEDIUMONLY &&
            (weight != System::MEDIUMWEIGHT ||
            ((GetMiiWeightClass(charSelect) != System::MEDIUMWEIGHT || RaceData::sInstance->menusScenario.localPlayerCount > 1) &&
            currentChar >= MII_S_A_MALE))){
                newButton->HandleDeselect(hudSlotId, -1);
                if (hudSlotId == 0) newButton = charSelect.GetButtonDriver(static_cast<CharacterId>(MARIO));
                else if (hudSlotId == 1) newButton = charSelect.GetButtonDriver(static_cast<CharacterId>(LUIGI));
                newButton->SelectInitialButton(hudSlotId);
                newButton->SetButtonColours(hudSlotId);
                page->OnButtonDriverSelect(newButton, newButton->buttonId, hudSlotId);
            }
            else if (charRestrict == System::CHAR_HEAVYONLY &&
            (weight != System::HEAVYWEIGHT ||
            ((GetMiiWeightClass(charSelect) != System::HEAVYWEIGHT || RaceData::sInstance->menusScenario.localPlayerCount > 1) &&
            currentChar >= MII_S_A_MALE))){
                newButton->HandleDeselect(hudSlotId, -1);
                if (hudSlotId == 0) newButton = charSelect.GetButtonDriver(static_cast<CharacterId>(WARIO));
                else if (hudSlotId == 1) newButton = charSelect.GetButtonDriver(static_cast<CharacterId>(WALUIGI));
                newButton->SelectInitialButton(hudSlotId);
                newButton->SetButtonColours(hudSlotId);
                page->OnButtonDriverSelect(newButton, newButton->buttonId, hudSlotId);
            }
        }
    }
    kmCall(0x807e33a8, RestrictCharacterSelection);
} // namespace UI
} // namespace VP