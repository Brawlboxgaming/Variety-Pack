#include <kamek.hpp>
#include <MarioKartWii/System/Random.hpp>
#include <MarioKartWii/Kart/KartDamage.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/Item/ItemManager.hpp>
#include <MarioKartWii/Item/ItemBehaviour.hpp>
#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <VP.hpp>

namespace VP {
namespace Race{

DamageType ApplyChaoticEffects(DamageType newDamage, u8 playerId);

void UpdateTimers(){
    if (!Pulsar::CupsConfig::IsRegsSituation()) {
        System *vp = System::GetsInstance();
        for (int i=0; i<12; ++i){
            if (vp->invincibilityTimer[i] > 0){
                --vp->invincibilityTimer[i];
            }
        }
    }
}

static RaceFrameHook UpdateTimerHook(UpdateTimers);

void ResetTimers(){
    if (!Pulsar::CupsConfig::IsRegsSituation()) {
        System *vp = System::GetsInstance();
        for (int i=0; i<12; ++i){
                vp->invincibilityTimer[i] = 0;
        }
    }
}

static RaceLoadHook ResetTimerHook(ResetTimers);

void InvincibilityFrames(Kart::Damage *kartDamage, DamageType newDamage, u32 r5, bool affectsMegas, DamageType* appliedDamage, u32 playerIdxItemPlayerSub, u32 r8){
    if (!Pulsar::CupsConfig::IsRegsSituation() && !IsBattle()) {
        const u8 playerId = kartDamage->link.GetPlayerIdx();
        const GameMode gameMode = RaceData::sInstance->racesScenario.settings.gamemode;
        const Gamemode vpGameMode = System::GetGamemode();
        System *vp = System::GetsInstance();
        if (vp->invincibilityTimer[playerId] > 0){
            return;
        }
        vp->invincibilityTimer[playerId] = 150;

        if (vpGameMode == RACESETTING_MODE_CHAOTIC){ // For Chaotic add item effects and damage
            newDamage = ApplyChaoticEffects(newDamage, playerId);
        }
    }
    if (newDamage != NO_DAMAGE) kartDamage->SetDamage(newDamage, r5, affectsMegas, appliedDamage, playerIdxItemPlayerSub, r8);
}

DamageType ApplyChaoticEffects(DamageType newDamage, u8 playerId){
    Random random;  
    u8 playerCount = Item::Manager::sInstance->playerCount;
    u8 position = RaceInfo::sInstance->players[playerId]->position;
    float third = static_cast<float>(position)/static_cast<float>(playerCount);

    int rnd;
    
    if (third <= 1.0f/3.0f){
        rnd = random.NextLimited(5);
        if (rnd < 4){
            // Damage
            if(random.NextLimited(2) > 0){
                int dmgRnd = random.NextLimited(18);
                if (dmgRnd == 16) dmgRnd = 14;
                newDamage = static_cast<DamageType>(dmgRnd);
            }
        }
        else{
            // Item
            int item;

            rnd = random.NextLimited(100);
            if (rnd < 5){
                item = MEGA_MUSHROOM;
            }
            else{
                item = MUSHROOM;
            }
            Item::Manager::sInstance->players[playerId].inventory.currentItemCount += 1;
            Item::Behaviour::behaviourTable[item].useFunction(Item::Manager::sInstance->players[playerId]);
            newDamage = NO_DAMAGE;
        }
    }
    
    else if (third <= 2.0f/3.0f){
        rnd = random.NextLimited(2);
        if (rnd < 1){
            // Damage
            if(random.NextLimited(2) > 0){
                int dmgRnd = random.NextLimited(18);
                if (dmgRnd == 16) dmgRnd = 14;
                newDamage = static_cast<DamageType>(dmgRnd);
            }
        }
        else{
            // Item
            int item;

            rnd = random.NextLimited(100);
            if (rnd < 30){
                item = MEGA_MUSHROOM;
            }
            else if (rnd < 60){
                item = STAR;
            }
            else if (rnd < 90){
                item = POW;
            }
            else{
                item = MUSHROOM;
            }
            Item::Manager::sInstance->players[playerId].inventory.currentItemCount += 1;
            Item::Behaviour::behaviourTable[item].useFunction(Item::Manager::sInstance->players[playerId]);
            newDamage = NO_DAMAGE;
        }
    }

    else{
        rnd = random.NextLimited(5);
        if (rnd < 4){
            // Item
            int item;

            rnd = random.NextLimited(100);
            if (rnd < 20){
                item = MEGA_MUSHROOM;
            }
            else if (rnd < 40 && !IsBattle()){
                item = LIGHTNING;
            }
            else if (rnd < 70 && !IsBattle()){
                item = BULLET_BILL;
            }
            else{
                item = STAR;
            }
            Item::Manager::sInstance->players[playerId].inventory.currentItemCount += 1;
            Item::Behaviour::behaviourTable[item].useFunction(Item::Manager::sInstance->players[playerId]);
            newDamage = NO_DAMAGE;
        }
        else{
            // Damage
            if(random.NextLimited(2) > 0){
                int dmgRnd = random.NextLimited(18);
                if (dmgRnd == 16) dmgRnd = 14;
                newDamage = static_cast<DamageType>(dmgRnd);
            }
        }
    }
    return newDamage;
}

kmCall(0x805700b0, InvincibilityFrames);
kmCall(0x805705d8, InvincibilityFrames);
kmCall(0x805721a4, InvincibilityFrames);
kmCall(0x805727b4, InvincibilityFrames);
kmBranch(0x80590d84, InvincibilityFrames);
} // namespace Race
} // namespace VP