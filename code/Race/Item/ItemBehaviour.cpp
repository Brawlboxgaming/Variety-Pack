#include <kamek.hpp>
#include <MarioKartWii/Item/ItemBehaviour.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>
#include <PulsarEngine/Settings/Settings.hpp>
#include <PulsarEngine/SlotExpansion/CupsConfig.hpp>
#include <VP.hpp>

namespace VP {
namespace Race{
static void ChangeItemBehaviour(){
    const Gamemode gamemode = System::GetGamemode();
    if (gamemode != GAMEMODE_NONE){
        Item::Behaviour *table = Item::Behaviour::behaviourTable;
        table[TRIPLE_BANANA].useType = Item::ITEMUSE_CIRCLE;
        table[BLUE_SHELL].useType = Item::ITEMUSE_FIRE;

        if (gamemode == GAMEMODE_BSS){
            table[BULLET_BILL].objId = OBJ_BLUE_SHELL;
            table[BULLET_BILL].useType = Item::ITEMUSE_CIRCLE;
            table[BULLET_BILL].numberOfItems = 0x3;
            table[TRIPLE_GREEN_SHELL].objId = OBJ_BLUE_SHELL;
        }

        if (gamemode == GAMEMODE_BBB){
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

static void ChangeBillOBJProperties(Item::ObjProperties* dest, const Item::ObjProperties& rel){
    new (dest) Item::ObjProperties(rel);
    if (System::GetGamemode() != GAMEMODE_NONE){
        dest->limit = 2;
    }
}

kmCall(0x80790bf4, ChangeBillOBJProperties);

static void ChangeBlueOBJProperties(Item::ObjProperties* dest, const Item::ObjProperties& rel){
    new (dest) Item::ObjProperties(rel);
    if(System::GetGamemode() == GAMEMODE_BSS){
        dest->limit = 30;
    }
}

kmCall(0x80790b74, ChangeBlueOBJProperties);

static void ChangeBombOBJProperties(Item::ObjProperties* dest, const Item::ObjProperties& rel){
    new (dest) Item::ObjProperties(rel);
    if(System::GetGamemode() == GAMEMODE_BBB){
        dest->limit = 30;
    }
}

kmCall(0x80790bb4, ChangeBombOBJProperties);
} // namespace Race
} // namespace VP