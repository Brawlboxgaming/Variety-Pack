#include <VP.hpp>
#include <MarioKartWii/UI/Page/Menu/KartSelect.hpp>

namespace VP {
namespace UI {
    u8 RestrictKartSelection(){
        SectionMgr::sInstance->sectionParams->kartsDisplayType = 2;
        System::KartRestriction kartRest = System::GetKartRestriction();
        if (kartRest == System::KART_KARTONLY) SectionMgr::sInstance->sectionParams->kartsDisplayType = 0;
        else if (kartRest == System::KART_BIKEONLY) SectionMgr::sInstance->sectionParams->kartsDisplayType = 1;
        return SectionMgr::sInstance->sectionParams->kartsDisplayType;
    }
    kmCall(0x808455a4, RestrictKartSelection);
    kmWrite32(0x808455a8, 0x907f06ec);

    bool IsKartAccessible(KartId kart, u32 r4){
        bool ret = IsKartUnlocked(kart, r4);
        System::KartRestriction kartRest = System::GetKartRestriction();

        if ((kart < STANDARD_BIKE_S && kartRest == System::KART_BIKEONLY) ||
            (kart >= STANDARD_BIKE_S && kartRest == System::KART_KARTONLY)){
            ret = false;
        }

        return ret;
    }
    kmCall(0x8084a45c, IsKartAccessible);
} // namespace UI
} // namespace VP