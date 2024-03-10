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

static void UpdateTimers(){
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

static void ResetTimers(){
    if (!Pulsar::CupsConfig::IsRegsSituation()) {
        System *vp = System::GetsInstance();
        for (int i=0; i<12; ++i){
                vp->invincibilityTimer[i] = 0;
        }
    }
}

static RaceLoadHook ResetTimerHook(ResetTimers);

static void InvincibilityFrames(Kart::Damage *kartDamage, DamageType newDamage, u32 r5, bool affectsMegas, DamageType* appliedDamage, u32 playerIdxItemPlayerSub, u32 r8){
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

kmCall(0x805700b0, InvincibilityFrames);
kmCall(0x805705d8, InvincibilityFrames);
kmCall(0x805721a4, InvincibilityFrames);
kmCall(0x805727b4, InvincibilityFrames);
kmBranch(0x80590d84, InvincibilityFrames);
} // namespace Race
} // namespace VP