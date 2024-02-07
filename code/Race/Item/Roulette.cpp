#include <kamek.hpp>
#include <VP.hpp>
#include <game/Item/ItemSlot.hpp>
#include <game/Item/ItemManager.hpp>
#include <game/Race/RaceData.hpp>
#include <game/Race/RaceInfo/RaceInfo.hpp>
#include <Pulsar/SlotExpansion/CupsDef.hpp>

int AccurateItemRoulette(Item::ItemSlotData *itemSlotData, u16 itemBoxType, u8 position, ItemId prevRandomItem, bool r7){
    const VP::Gamemode gamemode = VP::GetGamemode();
    if (gamemode != VP::Gamemode::RACESETTING_MODE_NONE){
        const u8 playerId = RaceInfo::sInstance->playerIdInEachPosition[position-1];
        const GameMode gameMode = RaceData::sInstance->racesScenario.settings.gamemode;
        if (gameMode != MODE_BATTLE && 
        gameMode != MODE_PRIVATE_BATTLE && 
        gameMode != MODE_PUBLIC_BATTLE){
            Item::Player *itemPlayer = &Item::Manager::sInstance->players[playerId];
            return itemSlotData->DecideItem(itemBoxType, position, itemPlayer->isHuman, 0x1, itemPlayer);
        }
    }
    return itemSlotData->DecideRouletteItem(itemBoxType, position, prevRandomItem, r7);
}
kmCall(0x807ba1e4, AccurateItemRoulette);
kmCall(0x807ba428, AccurateItemRoulette);
kmCall(0x807ba598, AccurateItemRoulette);