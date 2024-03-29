#include <MarioKartWii/Archive/ArchiveRoot.hpp>
#include <VP.hpp>

namespace VP {
namespace Race{
static void *GetCustomItemSlot(ArchiveRoot *archive, ArchiveSource type, const char *name, u32 *length){
    const Gamemode gamemode = System::GetGamemode();
    if (gamemode == GAMEMODE_NORMAL){
    name = "ItemSlot0.bin";
    }
    if (gamemode == GAMEMODE_BSS){
        name = "ItemSlot1.bin";
    }
    else if (gamemode == GAMEMODE_BBB){
        name = "ItemSlot2.bin";
    }
    else if (gamemode == GAMEMODE_CHAOTIC){
        name = "ItemSlot3.bin";
    }
    return archive->GetFile(type, name, length);
}
kmCall(0x807bb128, GetCustomItemSlot);
kmCall(0x807bb030, GetCustomItemSlot);
kmCall(0x807bb200, GetCustomItemSlot);
kmCall(0x807bb53c, GetCustomItemSlot);
kmCall(0x807bbb58, GetCustomItemSlot);

static void *GetCustomDriverParam(ArchiveRoot *archive, ArchiveSource type, const char *name, u32 *length){
    const Gamemode gamemode = System::GetGamemode();
    if (gamemode != GAMEMODE_NONE){
        name = "driverParamVP.bin";
    }
    return archive->GetFile(type, name, length);
}
kmCall(0x80591a54, GetCustomDriverParam);
} // namespace Race
} // namespace VP