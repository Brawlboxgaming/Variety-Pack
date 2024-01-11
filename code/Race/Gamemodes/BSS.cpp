#include <kamek.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/Race/RaceData.hpp>
#include <game/Race/RaceInfo/RaceInfo.hpp>
#include <game/Input/InputManager.hpp>
#include <game/Item/ItemManager.hpp>
#include <Common/ButtonCheck.hpp>
#include <Pulsar/SlotExpansion/CupsDef.hpp>
#include <VP.hpp>

bool BlueShellSwapping(bool hasItem){
    if (VP::GetGamemode() == VP::RACESETTING_MODE_BSS){
        for(int i=0; i<RaceData::sInstance->racesScenario.localPlayerCount; ++i){
            u8 hudPlayerId = RaceData::sInstance->racesScenario.settings.hudPlayerIds[i];
            Input::RealControllerHolder *controllerHolder = &Input::Manager::sInstance->realControllerHolders[i];
            ControllerType controllerType = controllerHolder->curController->GetType();
            if (hudPlayerId != 0xFF){
                ItemId currentItem = Item::Manager::sInstance->players[hudPlayerId].inventory.currentItemId;
                if (currentItem == BLUE_SHELL){
                    bool switchItem = false;
                    if(CheckButtonPressed(controllerHolder, controllerType, false, BUTTON_MINUS) ||
                    CheckButtonPressed(controllerHolder, controllerType, false, BUTTON_Y)){
                        switchItem = true;
                    }
                    if (switchItem){
                        Item::Manager::sInstance->players[hudPlayerId].inventory.currentItemId = TRIPLE_MUSHROOM;
                        u8 mushroomCount = 3;
                        u8 playerCount = Item::Manager::sInstance->playerCount;
                        u8 position = RaceInfo::sInstance->players[hudPlayerId]->position;
                        float third = (float)position/(float)playerCount;
                        if (third <= 1.0f/3.0f){
                            mushroomCount = 1;
                        }
                        else if (third <= 2.0f/3.0f){
                            mushroomCount = 2;
                        }

                        Item::Manager::sInstance->players[hudPlayerId].inventory.currentItemCount = mushroomCount;
                    }
                }
            }
        }
    }
    return hasItem;
}

kmBranch(0x807eeed0, BlueShellSwapping);