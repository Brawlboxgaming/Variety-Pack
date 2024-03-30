#include <VP.hpp>
#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <MarioKartWii/Kart/KartManager.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

namespace VP{
namespace Race{

static void UpdateTimer(){
    if (!Pulsar::CupsConfig::IsRegsSituation() && !IsBattle()) {
        System *vp = System::GetsInstance();
        for (int i = 0; i < GetLocalPlayerCount(); i++)
        {
            RaceData* raceData = RaceData::sInstance;
            RaceInfo* raceInfo = RaceInfo::sInstance;
            u32 playerId = raceData->GetPlayerIdOfLocalPlayer(i);
            Kart::Player *player = Kart::Manager::sInstance->GetKartPlayer(playerId);
            float currentRaceCompletion = raceInfo->players[playerId]->raceCompletion;
            RaceStage stage = raceInfo->stage;
            if(raceData->menusScenario.settings.gamemode != MODE_TIME_TRIAL){
                // if the race has not started, we do not want the timer to be changed from -1 (globally)
                if (stage >= RACESTAGE_RACE){
                    if (currentRaceCompletion <= vp->lastRaceCompletion[playerId]){
                        // if the race is over, we do not want them to be respawned (on per player basis)
                        if ((raceInfo->players[playerId]->stateFlags & 0x2) == 0x2){
                            vp->noRaceProgressionTimer[playerId] = -1;
                        }
                        // if someone has fallen off, we want their timer reset
                        else if((player->link.pointers->kartStatus->bitfield0 & 0x10) == 0x10 && vp->noRaceProgressionTimer[playerId] != -1){
                            vp->noRaceProgressionTimer[i] = 720;
                        }
                        // if someone is getting combo'd we don't want them to respawn, hence the damage check
                        else if (vp->noRaceProgressionTimer[playerId] > 0
                        && vp->noRaceProgressionTimer[playerId] != -1
                        && (player->link.pointers->kartStatus->bitfield1 & 0x1) != 0x1
                        ){
                            --vp->noRaceProgressionTimer[playerId];
                        }
                        else if (vp->noRaceProgressionTimer[playerId] == 0){
                            player->link.pointers->kartCollision->ActivateOob(1, 0, 0, 0);
                            --vp->noRaceProgressionTimer[playerId];
                        }
                    }
                    else{
                        vp->noRaceProgressionTimer[playerId] = 600;
                    }
                    vp->lastRaceCompletion[playerId] = currentRaceCompletion;  
                }
            }
        }
    }
}
static RaceFrameHook UpdateRaceProgTimerHook(UpdateTimer);

static void ResetTimer(){
    if (!Pulsar::CupsConfig::IsRegsSituation()){
        for (int i = 0; i < 4; i++) System::GetsInstance()->noRaceProgressionTimer[i] = -1;
    }
}
static RaceLoadHook ResetRaceProgTimerHook(ResetTimer);

} // namespace Race
} // namespace VP
