#include <VP.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuCharacterSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/CharacterSelect.hpp>

namespace VP {
namespace UI {
    // Uses the global function to get the character ID of the local player's Mii to determine it's weight class.
    WeightClass GetMiiWeightClass(Mii &mii){
        CharacterId charId = GetMiiCharacterId(mii);
        if (charId < MII_M_A_MALE){
            return LIGHTWEIGHT;
        }
        else if (charId < MII_L_A_MALE){
            return MEDIUMWEIGHT;
        }
        return HEAVYWEIGHT;
    }

    // "Enables" all the buttons on the character select screen by setting the images to the character panes and making all the buttons accessible.
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

    // Disables a specified button by setting the pane to a question mark and making the button inaccessible.
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
        CharacterRestriction charRestrict = System::GetCharacterRestriction();
        CtrlMenuCharacterSelect::ButtonDriver *driverButtons = charSelect.driverButtonsArray;
        CharacterId currentChar = page->models[hudSlotId].curCharacter;
        WeightClass weight = System::GetWeightClass(currentChar);
        WeightClass miiWeight = GetMiiWeightClass(page->localPlayerMiis[0]);
        CtrlMenuCharacterSelect::ButtonDriver *newButton = charSelect.GetButtonDriver(currentChar);

        EnableButtons(charSelect);

        // Disables the buttons that are not in the character weight class restriction.
        if (charRestrict != CHAR_DEFAULTSELECTION){
            for (int i = BUTTON_BABY_MARIO; i < BUTTON_MII_A; i++)
            {
                driverButtons[i].manipulator.inaccessible = false;
                if (charRestrict == CHAR_LIGHTONLY &&
                i >= BUTTON_MARIO && i < BUTTON_MII_A){
                    DisableButton(&driverButtons[i]);
                }
                if (charRestrict == CHAR_MEDIUMONLY &&
                ((i >= BUTTON_BABY_MARIO && i < BUTTON_MARIO) || (i >= BUTTON_WARIO && i < BUTTON_MII_A))){
                    DisableButton(&driverButtons[i]);
                }
                if (charRestrict == CHAR_HEAVYONLY &&
                i >= BUTTON_BABY_MARIO && i < BUTTON_WARIO){
                    DisableButton(&driverButtons[i]);
                }
            }

            // Disables the Miis in Local 2P no matter what.
            if (curSection == SECTION_P2_WIFI ||
            curSection == SECTION_P2_WIFI_FROOM_VS_VOTING ||
            curSection == SECTION_P2_WIFI_FROOM_TEAMVS_VOTING ||
            curSection == SECTION_P2_WIFI_FROOM_BALLOON_VOTING ||
            curSection == SECTION_P2_WIFI_FROOM_COIN_VOTING ||
            (charRestrict == CHAR_LIGHTONLY && miiWeight != LIGHTWEIGHT) ||
            (charRestrict == CHAR_MEDIUMONLY && miiWeight != MEDIUMWEIGHT) ||
            (charRestrict == CHAR_HEAVYONLY && miiWeight != HEAVYWEIGHT)){
                DisableButton(&driverButtons[BUTTON_MII_A]);
                DisableButton(&driverButtons[BUTTON_MII_B]);
            }
            // Changes the initially selected button to one that is not disabled.
            if (charRestrict == CHAR_LIGHTONLY &&
            ((weight != LIGHTWEIGHT && weight != MIIS) ||
            ((miiWeight != LIGHTWEIGHT || RaceData::sInstance->menusScenario.localPlayerCount > 1) &&
            currentChar >= MII_S_A_MALE))){
                button->HandleDeselect(hudSlotId, -1);
                if (hudSlotId == 0) newButton = charSelect.GetButtonDriver(static_cast<CharacterId>(BABY_MARIO));
                else if (hudSlotId == 1) newButton = charSelect.GetButtonDriver(static_cast<CharacterId>(BABY_LUIGI));
                newButton->SelectInitialButton(hudSlotId);
                newButton->SetButtonColours(hudSlotId);
                page->OnButtonDriverSelect(newButton, newButton->buttonId, hudSlotId);
            }
            else if (charRestrict == CHAR_MEDIUMONLY &&
            ((weight != MEDIUMWEIGHT && weight != MIIS) ||
            ((miiWeight != MEDIUMWEIGHT || RaceData::sInstance->menusScenario.localPlayerCount > 1) &&
            currentChar >= MII_S_A_MALE))){
                button->HandleDeselect(hudSlotId, -1);
                if (hudSlotId == 0) newButton = charSelect.GetButtonDriver(static_cast<CharacterId>(MARIO));
                else if (hudSlotId == 1) newButton = charSelect.GetButtonDriver(static_cast<CharacterId>(LUIGI));
                newButton->SelectInitialButton(hudSlotId);
                newButton->SetButtonColours(hudSlotId);
                page->OnButtonDriverSelect(newButton, newButton->buttonId, hudSlotId);
            }
            else if (charRestrict == CHAR_HEAVYONLY &&
            ((weight != HEAVYWEIGHT && weight != MIIS) ||
            ((miiWeight != HEAVYWEIGHT || RaceData::sInstance->menusScenario.localPlayerCount > 1) &&
            currentChar >= MII_S_A_MALE))){
                button->HandleDeselect(hudSlotId, -1);
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