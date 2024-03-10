#ifndef _VP_
#define _VP_
#include <kamek.hpp>
#include <PulsarEngine/PulsarSystem.hpp>
#include <PulsarEngine/Settings/Settings.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <VPEnums.hpp>

extern u32 RKNetController_Search1;
extern u32 RKNetController_Search2;
extern u32 RKNetController_Search3;
extern u32 RKNetController_Search4;
extern u32 RKNetController_Search5;
extern u32 RKNetController_Search6;
extern u32 RKNetController_Search7;
extern u32 RKNetController_Search8;

namespace VP {
class System : public Pulsar::System {
public:
    u8 invincibilityTimer[12];
    Transmission transmissions[12];
    Gamemode hostMode;
    KartRestriction kartRestrictMode;
    CharacterRestriction charRestrictMode;
    u32 lastSelectedTransmissionId;

    static Pulsar::System *Create(); //My Create function, needs to return Pulsar
    static System *GetsInstance(){ return static_cast<System *>(sInstance); } //for ease of use, optional
    static Gamemode GetGamemode();
    static KartRestriction GetKartRestriction();
    static CharacterRestriction GetCharacterRestriction();
    static WeightClass GetWeightClass(CharacterId id);
    static void CreateTransmissionSelectPage();

    u8 SetPackROOMMsg() override {
        hostMode = static_cast<Gamemode>(Pulsar::Settings::Mgr::GetSettingValue(static_cast<Pulsar::Settings::Type>(SETTINGSTYPE_VP), SETTINGVP_SCROLLER_MODE)); //2 bits
        kartRestrictMode = static_cast<KartRestriction>((Pulsar::Settings::Mgr::GetSettingValue(static_cast<Pulsar::Settings::Type>(SETTINGSTYPE_VP), SETTINGVP_RADIO_KARTSELECT))); //2 bits
        charRestrictMode = static_cast<CharacterRestriction>((Pulsar::Settings::Mgr::GetSettingValue(static_cast<Pulsar::Settings::Type>(SETTINGSTYPE_VP), SETTINGVP_RADIO_CHARSELECT))); //3 bits

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
} // namespace VP#
#endif