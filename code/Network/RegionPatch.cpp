#include <kamek.hpp>
#include <Pulsar/Settings/Settings.hpp>
#include <game/RKNet/RKNetController.hpp>
#include <VP.hpp>

void ChangeRegion(){
    RKNetController_Search1 = 0x38A00357;
    RKNetController_Search2 = 0x38C00357;
    RKNetController_Search3 = 0x38E00357;
    RKNetController_Search4 = 0x38E00357;
    RKNetController_Search5 = 0x38E00357;
    RKNetController_Search6 = 0x38E00357;
    RKNetController_Search7 = 0x38800057;
    RKNetController_Search8 = 0x38800057;
    if(Pulsar::Settings::Mgr::GetSettingValue(Pulsar::Settings::SETTINGSTYPE_RACE, VP::SETTINGRACE_SCROLLER_MODE) == VP::RACESETTING_MODE_BSS){
        RKNetController_Search1 = 0x38A00359;
        RKNetController_Search2 = 0x38C00359;
        RKNetController_Search3 = 0x38E00359;
        RKNetController_Search4 = 0x38E00359;
        RKNetController_Search5 = 0x38E00359;
        RKNetController_Search6 = 0x38E00359;
        RKNetController_Search7 = 0x38800059;
        RKNetController_Search8 = 0x38800059;
    }
    else if(Pulsar::Settings::Mgr::GetSettingValue(Pulsar::Settings::SETTINGSTYPE_RACE, VP::SETTINGRACE_SCROLLER_MODE) == VP::RACESETTING_MODE_BBB){
        RKNetController_Search1 = 0x38A0035a;
        RKNetController_Search2 = 0x38C0035a;
        RKNetController_Search3 = 0x38E0035a;
        RKNetController_Search4 = 0x38E0035a;
        RKNetController_Search5 = 0x38E0035a;
        RKNetController_Search6 = 0x38E0035a;
        RKNetController_Search7 = 0x3880005a;
        RKNetController_Search8 = 0x3880005a;
    }
    else if(Pulsar::Settings::Mgr::GetSettingValue(Pulsar::Settings::SETTINGSTYPE_RACE, VP::SETTINGRACE_SCROLLER_MODE) == VP::RACESETTING_MODE_CHAOTIC){
        RKNetController_Search1 = 0x38A00363;
        RKNetController_Search2 = 0x38C00363;
        RKNetController_Search3 = 0x38E00363;
        RKNetController_Search4 = 0x38E00363;
        RKNetController_Search5 = 0x38E00363;
        RKNetController_Search6 = 0x38E00363;
        RKNetController_Search7 = 0x38800063;
        RKNetController_Search8 = 0x38800063;
    }
    VP::CacheInvalidateAddress(RKNetController_Search1);
    VP::CacheInvalidateAddress(RKNetController_Search2);
    VP::CacheInvalidateAddress(RKNetController_Search3);
    VP::CacheInvalidateAddress(RKNetController_Search4);
    VP::CacheInvalidateAddress(RKNetController_Search5);
    VP::CacheInvalidateAddress(RKNetController_Search6);
    VP::CacheInvalidateAddress(RKNetController_Search7);
    VP::CacheInvalidateAddress(RKNetController_Search8);
}

Pulsar::Settings::Hook PatchSearchRegion(ChangeRegion);