#include <kamek.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <MarioKartWii/Input/InputManager.hpp>
#include <MarioKartWii/Item/ItemManager.hpp>
#include <Common/ButtonCheck.hpp>
#include <PulsarEngine/SlotExpansion/CupsConfig.hpp>
#include <VP.hpp>

namespace VP {
namespace Race{
static bool BlueShellSwapping(bool hasItem){
    if (System::GetGamemode() == RACESETTING_MODE_BSS){
        for(int i=0; i<RaceData::sInstance->racesScenario.localPlayerCount; ++i){
            u8 hudPlayerId = RaceData::sInstance->racesScenario.settings.hudPlayerIds[i];
            Input::RealControllerHolder *controllerHolder = &Input::Manager::sInstance->realControllerHolders[i];
            ControllerType controllerType = controllerHolder->curController->GetType();
            if (hudPlayerId != 0xFF){
                ItemId currentItem = Item::Manager::sInstance->players[hudPlayerId].inventory.currentItemId;
                if (currentItem == BLUE_SHELL){
                    bool switchItem = false;
                    if(Button::CheckPressed(controllerHolder, controllerType, false, Button::BUTTON_MINUS) ||
                    Button::CheckPressed(controllerHolder, controllerType, false, Button::BUTTON_Y)){
                        switchItem = true;
                    }
                    if (switchItem){
                        Item::Manager::sInstance->players[hudPlayerId].inventory.currentItemId = TRIPLE_MUSHROOM;
                        u8 mushroomCount = 3;
                        u8 playerCount = Item::Manager::sInstance->playerCount;
                        u8 position = RaceInfo::sInstance->players[hudPlayerId]->position;
                        float third = static_cast<float>(position)/static_cast<float>(playerCount);
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
} // namespace Race
} // namespace VP