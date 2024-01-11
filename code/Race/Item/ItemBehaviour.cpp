#include <kamek.hpp>
#include <game/Item/ItemBehaviour.hpp>
#include <game/Item/Obj/ItemObj.hpp>
#include <Pulsar/Settings/Settings.hpp>
#include <Pulsar/SlotExpansion/CupsDef.hpp>
#include <VP.hpp>

void ChangeItemBehaviour(){
    const VP::Gamemode gamemode = VP::GetGamemode();
    if (gamemode != VP::RACESETTING_MODE_NONE){
        Item::Behaviour *table = Item::Behaviour::behaviourTable;
        table[TRIPLE_BANANA].useType = Item::ITEMUSE_CIRCLE;
        table[BLUE_SHELL].useType = Item::ITEMUSE_FIRE;

        if (gamemode == VP::RACESETTING_MODE_BSS){
            table[BULLET_BILL].objId = OBJ_BLUE_SHELL;
            table[BULLET_BILL].useType = Item::ITEMUSE_CIRCLE;
            table[BULLET_BILL].numberOfItems = 0x3;
            table[TRIPLE_GREEN_SHELL].objId = OBJ_BLUE_SHELL;
        }

        if (gamemode == VP::RACESETTING_MODE_BBB){
            table[TRIPLE_GREEN_SHELL].objId = OBJ_BOBOMB;
            table[TRIPLE_GREEN_SHELL].useType = Item::ITEMUSE_CIRCLE;
            table[MUSHROOM].objId = OBJ_BOBOMB;
            table[MUSHROOM].useType = Item::ITEMUSE_FIRE;
            table[BULLET_BILL].objId = OBJ_BOBOMB;
            table[BULLET_BILL].useType = Item::ITEMUSE_CIRCLE;
            table[BULLET_BILL].numberOfItems = 0x3;
        }
    }
}
kmBranch(0x807bd1cc, ChangeItemBehaviour);

void ChangeBillOBJProperties(Item::ObjProperties* dest, const Item::ObjProperties& rel){
    new (dest) Item::ObjProperties(rel);
    if (VP::GetGamemode() != VP::RACESETTING_MODE_NONE){
        dest->limit = 2;
    }
}

kmCall(0x80790bf4, ChangeBillOBJProperties);

void ChangeBlueOBJProperties(Item::ObjProperties* dest, const Item::ObjProperties& rel){
    new (dest) Item::ObjProperties(rel);
    if(VP::GetGamemode() == VP::RACESETTING_MODE_BSS){
        dest->limit = 20;
    }
}

kmCall(0x80790b74, ChangeBlueOBJProperties);

void ChangeBombOBJProperties(Item::ObjProperties* dest, const Item::ObjProperties& rel){
    new (dest) Item::ObjProperties(rel);
    if(VP::GetGamemode() == VP::RACESETTING_MODE_BBB){
        dest->limit = 20;
    }
}

kmCall(0x80790bb4, ChangeBombOBJProperties);