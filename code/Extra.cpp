#include <kamek.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceResult.hpp>
#include <game/Race/RaceData.hpp>
#include <game/Race/RaceInfo/RaceInfo.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <core/rvl/devfs/isfs.hpp>
#include <core/rvl/os/OS.hpp>
#include <Pulsar/Race/200ccParams.hpp>
#include <game/GlobalFunctions.hpp>
#include <Pulsar/SlotExpansion/CupsDef.hpp>
#include <game/Item/Obj/Bomb.hpp>
#include <VP.hpp>

// Don't Lose VR When Disconnecting
kmWrite32(0x80856560, 0x60000000);

// Coloured Minimap
kmWrite32(0x807DFC24, 0x60000000);

void VSPointsSystem(){
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

                const s32 finishTime = finishTimer->milliseconds + finishTimer->seconds*1000 + finishTimer->minutes*60000;
                if (finishTime != 0){
                    const s32 finishTimeOf1st = finishTimerOf1st->milliseconds + finishTimerOf1st->seconds*1000 + finishTimerOf1st->minutes*60000;

                    const s32 timeDifference = (finishTime - finishTimeOf1st)/1000;

                    if (timeDifference < 30){
                        scenario.players[playerId].score = scenario.players[playerId].previousScore + (30-timeDifference);
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

void LoadOriginalItemboxes(g3d::ResFile &file, ArchiveSource type, const char *brresName, const g3d::ResFile& fallBack){
    if (strcmp(brresName, "itembox.brres") == 0){
        type = ARCHIVE_HOLDER_COMMON;
    }
    ModelDirector::BindBRRESFallback(file, type, brresName, fallBack);
}
kmCall(0x8081fdb4, LoadOriginalItemboxes);

void LoadCustomFakeItemboxes(g3d::ResFile &file, ArchiveSource type, const char *brresName){
    if (strcmp(brresName, "itemBoxNiseRtpa.brres") == 0 && VP::GetGamemode() != VP::RACESETTING_MODE_NONE){
        brresName = "itemBoxNiseRtpaVP.brres";
    }
    ModelDirector::BindBRRES(file, type, brresName);
}
kmCall(0x807a0160, LoadCustomFakeItemboxes);

void MotionSensorBombs1(Item::ObjBomb* obj){
    int timer = 300;
    if (VP::GetGamemode() != VP::RACESETTING_MODE_NONE){
        timer = 4095;
    }
    obj->timer = timer;
    obj->Item::Obj::SpawnModel();
}
kmCall(0x807a5be4, MotionSensorBombs1);
kmWrite32(0x807a5c10, 0x60000000); // nope the store of the timer

void MotionSensorBombs2(Item::ObjBomb* obj, UnkType r4, UnkType r5, UnkType r6, float f1, float f2, float f3){
    func_807b7104(obj, r4, r5, r6, f1, f2, f3);
    int timer = 90;
    if (VP::GetGamemode() != VP::RACESETTING_MODE_NONE){
        timer = 4095;
    }
    obj->timer = timer;
}
kmCall(0x807a4ac4, MotionSensorBombs2);
kmWrite32(0x807a4acc, 0x60000000); // nop the store of the timer