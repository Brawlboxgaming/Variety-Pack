#include <kamek.hpp>
#include <PulsarEngine/PulsarSystem.hpp>
#include <PulsarEngine/Settings/Settings.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>

extern u32 RKNetController_Search1;
extern u32 RKNetController_Search2;
extern u32 RKNetController_Search3;
extern u32 RKNetController_Search4;
extern u32 RKNetController_Search5;
extern u32 RKNetController_Search6;
extern u32 RKNetController_Search7;
extern u32 RKNetController_Search8;

extern void func_807b7104(Item::Obj* obj, UnkType r4, UnkType r5, UnkType r6, float f1, float f2, float f3);

namespace VP {
class System : public Pulsar::System {
public:
    enum Gamemode{
        RACESETTING_MODE_NORMAL = 0x0,
        RACESETTING_MODE_BSS = 0x1,
        RACESETTING_MODE_BBB = 0x2,
        RACESETTING_MODE_CHAOTIC = 0x3,
        RACESETTING_MODE_NONE = 0x4
    };
    
    enum ExtraSettings{ // +6 for scrollers
        // Race
        SETTINGRACE_SCROLLER_MODE = 0 + 6,

        // Menu
        SETTINGMENU_RADIO_MUSIC = 1
    };

    enum BMGIds{
        RADIO_MUSIC_TITLE = 0x3001,
        RADIO_MUSIC_DISABLED = 0x3020,
        RADIO_MUSIC_ENABLED = 0x3021,
        RADIO_MUSIC_DISABLED_DESC = 0x3200,
        RADIO_MUSIC_ENABLED_DESC = 0x3201,
        SCROLLER_MODE_TITLE = 0x4700,
        SCROLLER_MODE_NONE = 0x4710,
        SCROLLER_MODE_BSS = 0x4711,
        SCROLLER_MODE_BBB = 0x4712,
        SCROLLER_MODE_CHAOTIC = 0x4713,
        SCROLLER_MODE_NONE_DESC = 0x4800,
        SCROLLER_MODE_BSS_DESC = 0x4801,
        SCROLLER_MODE_BBB_DESC = 0x4802,
        SCROLLER_MODE_CHAOTIC_DESC = 0x4803
    };

    u8 invincibilityTimer[12];
    Gamemode hostMode;

    static Pulsar::System *Create(); //My Create function, needs to return Pulsar
    static System *GetsInstance(){return static_cast<System *>(sInstance);} //for ease of use, optional
    static Gamemode GetGamemode();

    u8 SetPackROOMMsg() override {
        hostMode = static_cast<System::Gamemode>(Pulsar::Settings::Mgr::GetSettingValue(Pulsar::Settings::SETTINGSTYPE_RACE, System::SETTINGRACE_SCROLLER_MODE));
        return hostMode;
    };
    void ParsePackROOMMsg(u8 msg) override {
        hostMode = static_cast<System::Gamemode>(msg);
    };
    void AfterInit() override;

    static inline void CacheInvalidateAddress(register u32 address) {
        asm(dcbst 0, address;);
        asm(sync;);
        asm(icbi 0, address;);
        asm(isync;);
    }
};
} // namespace VP