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
} // namespace Race
} // namespace VP