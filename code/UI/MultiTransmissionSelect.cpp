#include <UI/MultiTransmissionSelect.hpp>

namespace VP{
namespace UI{
    static void BuildMultiTransmissionSelect(Section& section, PageId id){
        section.CreateAndInitPage(id);
        PageId newId = static_cast<PageId>(PAGE_MULTI_TRANSMISSION_SELECT);
        MultiTransmissionSelect* transmission = new(MultiTransmissionSelect);
        section.Set(transmission, newId);
        transmission->Init(newId);
    }
    kmCall(0x8062db5c, BuildMultiTransmissionSelect); //0x54
    kmCall(0x8062e36c, BuildMultiTransmissionSelect); //0x5B
    kmCall(0x8062e510, BuildMultiTransmissionSelect); //0x5C
    kmCall(0x8062e6b4, BuildMultiTransmissionSelect); //0x5D

    static void LoadMultiTransmissionFromKart(Pages::Menu* menu, PageId pageId, float delay){
        if (!Pulsar::CupsConfig::IsRegsSituation() && VP::System::GetTransmission()){
            pageId = static_cast<PageId>(PAGE_MULTI_TRANSMISSION_SELECT);
        }
        menu->LoadNextPageWithDelayById(pageId, delay);
    }
    kmCall(0x8084a218, LoadMultiTransmissionFromKart);
    kmCall(0x8084a24c, LoadMultiTransmissionFromKart);

    static void LoadMultiTransmissionFromDrift(Pages::Menu* menu, float delay){
        if (!Pulsar::CupsConfig::IsRegsSituation() && VP::System::GetTransmission()){
            menu->prevPageId = static_cast<PageId>(PAGE_MULTI_TRANSMISSION_SELECT);
        }
        menu->LoadPrevPageWithDelay(delay);
    }
    kmCall(0x8084b8a8, LoadMultiTransmissionFromDrift);

    MultiTransmissionSelect::MultiTransmissionSelect(){
        nextPageId = PAGE_MULTIPLAYER_DRIFT_SELECT;
        prevPageId = PAGE_MULTIPLAYER_KART_SELECT;
        onButtonClickHandler.ptmf = &MultiTransmissionSelect::OnButtonClick;
        onBackPressHandler.ptmf = &MultiTransmissionSelect::OnBackPress;
    }

    void MultiTransmissionSelect::OnActivate(){
        for (int i = 0; i < this->externControlCount; i+=2){
            this->externControls[i]->SetMessage(MENU_TRANSMISSION_OUTSIDE);
            this->externControls[i+1]->SetMessage(MENU_TRANSMISSION_INSIDE);
        }
        this->titleBmg = MENU_TRANSMISSION_TITLE;
        MenuInteractable::OnActivate();
        for (int i = 0; i < GetLocalPlayerCount(); i++)
        {
            this->controlsManipulatorManager.holders[i].info.enabled = true;
            this->externControls[i*2]->isHidden = false;
            this->externControls[i*2]->manipulator.inaccessible = false;
            this->externControls[i*2+1]->isHidden = false;
            this->externControls[i*2+1]->manipulator.inaccessible = false;
        }
    }

    void MultiTransmissionSelect::SetButtonHandlers(PushButton& button){
        button.SetOnClickHandler(this->onButtonClickHandler, 0);
        button.SetOnDeselectHandler(this->onButtonDeselectHandler);
    }

    int MultiTransmissionSelect::GetActivePlayerBitfield() const {
        return this->activePlayerBitfield;
    }

    int MultiTransmissionSelect::GetPlayerBitfield() const {
        return this->playerBitfield;
    }

    ManipulatorManager& MultiTransmissionSelect::GetManipulatorManager(){
        return this->controlsManipulatorManager;
    }

    void MultiTransmissionSelect::OnButtonClick(PushButton& button, u32 hudSlotId){
        this->activePlayerBitfield += (1 << hudSlotId);
        System* vp = System::GetsInstance();
        switch (button.buttonId)
        {
            case 0:
            case 2:
            case 4:
            case 6:
                if (hudSlotId == 0) vp->lastSelectedTransmission = TRANSMISSION_OUTSIDE;
                vp->transmissions[hudSlotId] = TRANSMISSION_OUTSIDE;
                this->externControls[button.buttonId+1]->isHidden = true;
                this->externControls[button.buttonId+1]->manipulator.inaccessible = true;
                break;
            case 1:
            case 3:
            case 5:
            case 7:
                if (hudSlotId == 0) vp->lastSelectedTransmission = TRANSMISSION_INSIDE;
                vp->transmissions[hudSlotId] = TRANSMISSION_INSIDE;
                this->externControls[button.buttonId-1]->isHidden = true;
                this->externControls[button.buttonId-1]->manipulator.inaccessible = true;
                break;
            default:
                break;
        }
        this->controlsManipulatorManager.holders[hudSlotId].info.enabled = false;
        bool allPlayersSelected = AreAllPlayersActive();
        if (allPlayersSelected) this->LoadNextPageById(PAGE_MULTIPLAYER_DRIFT_SELECT, button);
    }

    void MultiTransmissionSelect::OnBackPress(u32 hudSlotId){
        if (!this->controlsManipulatorManager.holders[hudSlotId].info.enabled){
            this->controlsManipulatorManager.holders[hudSlotId].info.enabled = true;
            this->externControls[hudSlotId*2]->isHidden = false;
            this->externControls[hudSlotId*2]->manipulator.inaccessible = false;
            this->externControls[hudSlotId*2+1]->isHidden = false;
            this->externControls[hudSlotId*2+1]->manipulator.inaccessible = false;
            this->PlaySound(6, 0); // Back Press sound
            this->activePlayerBitfield -= (1 << hudSlotId);
        }
        else{
            for (int i = 0; i < GetLocalPlayerCount(); i++)
            {
                this->controlsManipulatorManager.holders[i].info.enabled = true;
            }
            this->LoadPrevPageWithDelay(0.0f);
        }
    }

    void MultiTransmissionSelect::BeforeControlUpdate(){
        SectionMgr* sectionMgr = SectionMgr::sInstance;
        Pulsar::UI::ExpCharacterSelect* charSelect = sectionMgr->curSection->Get<Pulsar::UI::ExpCharacterSelect>();
        if(charSelect->rouletteCounter != -1 && this->currentState == 0x4) {
            this->controlsManipulatorManager.inaccessible = true;
            for(int i = 0; i < sectionMgr->sectionParams->localPlayerCount; ++i) {
                Random random;
                PushButton* randomTransmission = this->externControls[(i * 2) + random.NextLimited(2)];
                randomTransmission->HandleClick(i, -1);
            }
        }
    }

    void FixMultiVehicleModelTransition(VehicleModelControl* ctrl, PageId id){
        if(id == static_cast<PageId>(PAGE_MULTI_TRANSMISSION_SELECT)){
            id = PAGE_MULTIPLAYER_DRIFT_SELECT;
        }
        ctrl->SetAnimationType(id);
    };
    kmCall(0x8084a770, FixMultiVehicleModelTransition);
    kmCall(0x8084a6dc, FixMultiVehicleModelTransition);

} // namespace UI
} // namespace VP