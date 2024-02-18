#include <kamek.hpp>
#include <PulsarEngine/PulsarSystem.hpp>
#include <PulsarEngine/Settings/Settings.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>

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
    enum CharButtonId{
        BUTTON_BABY_MARIO,
        BUTTON_BABY_LUIGI,
        BUTTON_TOAD,
        BUTTON_TOADETTE,
        BUTTON_BABY_PEACH,
        BUTTON_BABY_DAISY,
        BUTTON_KOOPA_TROOPA,
        BUTTON_DRY_BONES,
        BUTTON_MARIO,
        BUTTON_LUIGI,
        BUTTON_YOSHI,
        BUTTON_BIRDO,
        BUTTON_PEACH,
        BUTTON_DAISY,
        BUTTON_DIDDY_KONG,
        BUTTON_BOWSER_JR,
        BUTTON_WARIO,
        BUTTON_WALUIGI,
        BUTTON_KING_BOO,
        BUTTON_ROSALINA,
        BUTTON_DONKEY_KONG,
        BUTTON_FUNKY_KONG,
        BUTTON_BOWSER,
        BUTTON_DRY_BOWSER,
        BUTTON_MII_A,
        BUTTON_MII_B
    };

    enum WeightClass{
        LIGHTWEIGHT,
        MEDIUMWEIGHT,
        HEAVYWEIGHT,
        MIIS
    };

    enum Gamemode{
        RACESETTING_MODE_NORMAL = 0x0,
        RACESETTING_MODE_BSS = 0x1,
        RACESETTING_MODE_BBB = 0x2,
        RACESETTING_MODE_CHAOTIC = 0x3,
        RACESETTING_MODE_NONE = 0x4
    };

    enum KartRestriction{
        KART_DEFAULTSELECTION,
        KART_KARTONLY,
        KART_BIKEONLY
    };

    enum CharacterRestriction{
        CHAR_DEFAULTSELECTION,
        CHAR_LIGHTONLY,
        CHAR_MEDIUMONLY,
        CHAR_HEAVYONLY
    };
    
    enum ExtraSettingType{
        SETTINGSTYPE_VP = 3
    };

    enum ExtraSettings{ // +6 for scrollers
        SETTINGVP_RADIO_MUSIC = 0,

        SETTINGVP_SCROLLER_MODE = 0 + 6,

        SETTINGHOST_RADIO_KARTSELECT = 3,
        SETTINGHOST_RADIO_CHARSELECT = 4
    };

    enum BMGIds{
        SETTINGVP_BUTTONCHANGE = 0x2f04,
        SETTINGVP_BUTTONCHANGE_DESC = 0x2f14,
        SETTINGVP_PAGE_DESC = 0x2f24,

        RADIO_MUSIC_TITLE = 0x6000,
        RADIO_MUSIC_DISABLED = 0x6010,
        RADIO_MUSIC_ENABLED = 0x6011,
        RADIO_MUSIC_DISABLED_DESC = 0x6100,
        RADIO_MUSIC_ENABLED_DESC = 0x6101,

        RADIO_KARTSELECT_TITLE = 0x5003,
        RADIO_KARTSELECT_DEFAULT = 0x5040,
        RADIO_KARTSELECT_KARTONLY = 0x5041,
        RADIO_KARTSELECT_BIKEONLY = 0x5042,
        RADIO_KARTSELECT_DEFAULT_DESC = 0x5400,
        RADIO_KARTSELECT_KARTONLY_DESC = 0x5401,
        RADIO_KARTSELECT_BIKEONLY_DESC = 0x5402,

        RADIO_CHARSELECT_TITLE = 0x5004,
        RADIO_CHARSELECT_DEFAULT = 0x5050,
        RADIO_CHARSELECT_LIGHTONLY = 0x5051,
        RADIO_CHARSELECT_MEDIUMONLY = 0x5052,
        RADIO_CHARSELECT_HEAVYONLY  = 0x5053,
        RADIO_CHARSELECT_DEFAULT_DESC = 0x5500,
        RADIO_CHARSELECT_LIGHTONLY_DESC = 0x5501,
        RADIO_CHARSELECT_MEDIUMONLY_DESC = 0X5502,
        RADIO_CHARSELECT_HEAVYONLY_DESC = 0x5503,
        
        SCROLLER_MODE_TITLE = 0x6700,
        SCROLLER_MODE_NONE = 0x6710,
        SCROLLER_MODE_BSS = 0x6711,
        SCROLLER_MODE_BBB = 0x6712,
        SCROLLER_MODE_CHAOTIC = 0x6713,
        SCROLLER_MODE_NONE_DESC = 0x6800,
        SCROLLER_MODE_BSS_DESC = 0x6801,
        SCROLLER_MODE_BBB_DESC = 0x6802,
        SCROLLER_MODE_CHAOTIC_DESC = 0x6803
    };

    u8 invincibilityTimer[12];
    Gamemode hostMode;
    KartRestriction kartRestrictMode;
    CharacterRestriction charRestrictMode;

    static Pulsar::System *Create(); //My Create function, needs to return Pulsar
    static System *GetsInstance(){return static_cast<System *>(sInstance);} //for ease of use, optional
    static Gamemode GetGamemode();
    static KartRestriction GetKartRestriction();
    static CharacterRestriction GetCharacterRestriction();
    static WeightClass GetWeightClass(CharacterId id);

    u8 SetPackROOMMsg() override {
        hostMode = static_cast<Gamemode>(Pulsar::Settings::Mgr::GetSettingValue(static_cast<Pulsar::Settings::Type>(SETTINGSTYPE_VP), SETTINGVP_SCROLLER_MODE)); //2 bits
        kartRestrictMode = static_cast<KartRestriction>((Pulsar::Settings::Mgr::GetSettingValue(Pulsar::Settings::SETTINGSTYPE_HOST, SETTINGHOST_RADIO_KARTSELECT))); //2 bits
        charRestrictMode = static_cast<CharacterRestriction>((Pulsar::Settings::Mgr::GetSettingValue(Pulsar::Settings::SETTINGSTYPE_HOST, SETTINGHOST_RADIO_CHARSELECT))); //3 bits

        u8 ret = hostMode + (kartRestrictMode << 2) + (charRestrictMode << 4);

        return ret;
    };
    void ParsePackROOMMsg(u8 msg) override {
        hostMode = static_cast<Gamemode>(msg & 0b11);
        kartRestrictMode = static_cast<KartRestriction>((msg & 0b1100) >> 2);
        charRestrictMode = static_cast<CharacterRestriction>((msg & 0b1110000) >> 4);
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