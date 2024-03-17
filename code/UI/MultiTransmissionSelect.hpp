#ifndef _MULTI_TRANSMISSION_SELECT_
#define _MULTI_TRANSMISSION_SELECT_
#include <VP.hpp>
#include <MarioKartWii/UI/Page/Menu/KartSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/MultiDriftSelect.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/UI/Page/Other/Message.hpp>

namespace VP{
namespace UI{
class MultiTransmissionSelect : public Pages::MultiDriftSelect {
public:
    static const PageId id = static_cast<PageId>(PAGE_MULTI_TRANSMISSION_SELECT);
    MultiTransmissionSelect();
    void OnActivate() override;
    void SetButtonHandlers(PushButton& pushButton) override;
    int GetActivePlayerBitfield() const override;
    int GetPlayerBitfield() const override;
    ManipulatorManager& GetManipulatorManager() override;
private:
    void OnButtonClick(PushButton& button, u32 hudSlotId);
    void OnBackPress(u32 hudSlotId);
};
} // namespace UI
} // namespace VP
#endif