#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceResult.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceGhostDiffTime.hpp>
#include <core/rvl/devfs/isfs.hpp>
#include <core/rvl/os/OS.hpp>
#include <PulsarEngine/Race/200ccParams.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <PulsarEngine/SlotExpansion/CupsConfig.hpp>
#include <MarioKartWii/Item/Obj/Bomb.hpp>
#include <VP.hpp>

namespace VP {
namespace Race{
// Don't Lose VR When Disconnecting
kmWrite32(0x80856560, 0x60000000);

static void VSPointsSystem(){
    if (!IsBattle()){
        RacedataScenario &scenario = RaceData::sInstance->menusScenario;
        const RaceInfo *raceinfo = RaceInfo::sInstance;
        for (int i = 0; i < scenario.playerCount; ++i){
            const u8 playerId = raceinfo->playerIdInEachPosition[i];
            const u8 playerIdOf1st = raceinfo->playerIdInEachPosition[0];
            if (playerId == playerIdOf1st){
                scenario.players[playerId].score = scenario.players[playerId].previousScore + 35;
            }
            else{
                const Timer *finishTimer = raceinfo->players[playerId]->raceFinishTime;
                const Timer *finishTimerOf1st = raceinfo->players[playerIdOf1st]->raceFinishTime;
                if (finishTimer->isActive){
                    const Timer diffTimer = CtrlRaceGhostDiffTime::SubtractTimers(*finishTimer, *finishTimerOf1st);
                    const s32 diff = diffTimer.seconds + diffTimer.minutes*60;

                    if (diff < 30){
                        scenario.players[playerId].score = scenario.players[playerId].previousScore + (30-diff);
                    }
                    else{
                        scenario.players[playerId].score = scenario.players[playerId].previousScore;
                    }
                }
            }
        }
    }
}
kmBranch(0x8052ed14, VSPointsSystem);

static void LoadOriginalItemboxes(g3d::ResFile &file, ArchiveSource type, const char *brresName, const g3d::ResFile& fallBack){
    if (strcmp(brresName, "itembox.brres") == 0){
        type = ARCHIVE_HOLDER_COMMON;
    }
    ModelDirector::BindBRRESFallback(file, type, brresName, fallBack);
}
kmCall(0x8081fdb4, LoadOriginalItemboxes);

static void LoadCustomFakeItemboxes(g3d::ResFile &file, ArchiveSource type, const char *brresName){
    if (strcmp(brresName, "itemBoxNiseRtpa.brres") == 0 && System::GetGamemode() != RACESETTING_MODE_NONE){
        brresName = "itemBoxNiseRtpaVP.brres";
    }
    ModelDirector::BindBRRES(file, type, brresName);
}
kmCall(0x807a0160, LoadCustomFakeItemboxes);

static void DropMotionSensorBombs(Item::ObjBomb* obj){
    int timer = 300;
    if (System::GetGamemode() != RACESETTING_MODE_NONE){
        timer = 4095;
    }
    obj->timer = timer;
    obj->Item::Obj::SpawnModel();
}
kmCall(0x807a5be4, DropMotionSensorBombs);
kmWrite32(0x807a5c10, 0x60000000); // nope the store of the timer

static void ThrowMotionSensorBombs(Item::ObjBomb* obj, Item::PlayerSub& playerSub, u32 groundEffectDelay, bool isThrow, float speed, float throwHeight, float dropHeight){
    obj->SetInitialPositionImpl(playerSub, groundEffectDelay, isThrow, speed, throwHeight, dropHeight);
    int timer = 90;
    if (System::GetGamemode() != RACESETTING_MODE_NONE){
        timer = 4095;
    }
    obj->timer = timer;
}
kmCall(0x807a4ac4, ThrowMotionSensorBombs);
kmWrite32(0x807a4acc, 0x60000000); // nop the store of the timer
} // namespace Race
} // namespace VP