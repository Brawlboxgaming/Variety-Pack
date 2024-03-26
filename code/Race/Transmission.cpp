#include <VP.hpp>

namespace VP{
namespace Race{
    static KartType GetCustomKartType(Kart::Link* link){
        if (!Pulsar::CupsConfig::IsRegsSituation()){
            RaceData *raceData = RaceData::sInstance;
            u8 playerId = link->GetPlayerIdx();
            u8 hudSlotId = raceData->GetHudSlotId(playerId);
            PlayerType playerType = raceData->racesScenario.players[playerId].playerType;
            link->pointers->values->statsAndBsp.stats->targetAngle = 45;
            u8 chosenType;
            chosenType = System::GetsInstance()->transmissions[hudSlotId];
            if (chosenType == TRANSMISSION_OUTSIDE){
                if (link->pointers->values->statsAndBsp.stats->type == KART){
                    return KART;
                }
                return OUTSIDE_BIKE;
            }
            else if(chosenType == TRANSMISSION_INSIDE) return INSIDE_BIKE;
            return link->pointers->values->statsAndBsp.stats->type;
        }
        return link->pointers->values->statsAndBsp.stats->type;
    }
    kmBranch(0x80590a10, GetCustomKartType);

    static void SetCPUKartType(){
        Random random;
        u8 localPlayerCount = GetLocalPlayerCount();
        for (int i = localPlayerCount; i < 12; ++i){
            VP::System* vp = System::GetsInstance();
            PlayerType playerType = RaceData::sInstance->racesScenario.players[i].playerType;
            if (playerType == PLAYER_CPU && vp->transmissions[i] == 0){
                Transmission type = static_cast<Transmission>(random.NextLimited(2) + 1);
                vp->transmissions[i] = type;
            }
        }
    }
    static RaceLoadHook SetCPUKartTypeHook(SetCPUKartType);

    static void ResetTransmissions(){
        RaceData *raceData = RaceData::sInstance;
        for (int i = 0; i < 12; ++i){
            System::GetsInstance()->transmissions[i] = TRANSMISSION_DEFAULT;
        }
    }
    kmBranch(0x80530158, ResetTransmissions);
} // namespace Race
} // namespace VP