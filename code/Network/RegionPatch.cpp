#include <kamek.hpp>
#include <PulsarEngine/Settings/Settings.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <VP.hpp>

namespace VP {
namespace Network{
void ChangeRegion(){
    RKNetController_Search1 = 0x38A00357;
    RKNetController_Search2 = 0x38C00357;
    RKNetController_Search3 = 0x38E00357;
    RKNetController_Search4 = 0x38E00357;
    RKNetController_Search5 = 0x38E00357;
    RKNetController_Search6 = 0x38E00357;
    RKNetController_Search7 = 0x38800057;
    RKNetController_Search8 = 0x38800057;
    if(System::GetGamemode() == System::RACESETTING_MODE_BSS){
        RKNetController_Search1 = 0x38A00359;
        RKNetController_Search2 = 0x38C00359;
        RKNetController_Search3 = 0x38E00359;
        RKNetController_Search4 = 0x38E00359;
        RKNetController_Search5 = 0x38E00359;
        RKNetController_Search6 = 0x38E00359;
        RKNetController_Search7 = 0x38800059;
        RKNetController_Search8 = 0x38800059;
    }
    else if(System::GetGamemode() == System::RACESETTING_MODE_BBB){
        RKNetController_Search1 = 0x38A0035a;
        RKNetController_Search2 = 0x38C0035a;
        RKNetController_Search3 = 0x38E0035a;
        RKNetController_Search4 = 0x38E0035a;
        RKNetController_Search5 = 0x38E0035a;
        RKNetController_Search6 = 0x38E0035a;
        RKNetController_Search7 = 0x3880005a;
        RKNetController_Search8 = 0x3880005a;
    }
    else if(System::GetGamemode() == System::RACESETTING_MODE_CHAOTIC){
        RKNetController_Search1 = 0x38A00363;
        RKNetController_Search2 = 0x38C00363;
        RKNetController_Search3 = 0x38E00363;
        RKNetController_Search4 = 0x38E00363;
        RKNetController_Search5 = 0x38E00363;
        RKNetController_Search6 = 0x38E00363;
        RKNetController_Search7 = 0x38800063;
        RKNetController_Search8 = 0x38800063;
    }
    System::CacheInvalidateAddress(RKNetController_Search1);
    System::CacheInvalidateAddress(RKNetController_Search2);
    System::CacheInvalidateAddress(RKNetController_Search3);
    System::CacheInvalidateAddress(RKNetController_Search4);
    System::CacheInvalidateAddress(RKNetController_Search5);
    System::CacheInvalidateAddress(RKNetController_Search6);
    System::CacheInvalidateAddress(RKNetController_Search7);
    System::CacheInvalidateAddress(RKNetController_Search8);
}

Pulsar::Settings::Hook PatchSearchRegion(ChangeRegion);
} // namespace Network
} // namespace VP