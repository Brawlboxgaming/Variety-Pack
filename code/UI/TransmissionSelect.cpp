#include <UI/TransmissionSelect.hpp>

namespace VP{
namespace UI{
    static void BuildTransmissionSelect(Section& section, PageId id){
        section.CreateAndInitPage(id);
        PageId newId = static_cast<PageId>(PAGE_TRANSMISSION_SELECT);
        TransmissionSelect* transmission = new(TransmissionSelect);
        section.Set(transmission, newId);
        transmission->Init(newId);
    }
    kmCall(0x8062d334, BuildTransmissionSelect); //0x48
    kmCall(0x8062d478, BuildTransmissionSelect); //0x49
    kmCall(0x8062d5bc, BuildTransmissionSelect); //0x4A
    kmCall(0x8062d808, BuildTransmissionSelect); //0x4D
    kmCall(0x8062d874, BuildTransmissionSelect); //0x4E
    kmCall(0x8062d8e0, BuildTransmissionSelect); //0x4F
    kmCall(0x8062d94c, BuildTransmissionSelect); //0x50
    kmCall(0x8062dd00, BuildTransmissionSelect); //0x55
    kmCall(0x8062dea4, BuildTransmissionSelect); //0x56
    kmCall(0x8062e048, BuildTransmissionSelect); //0x57

    static void LoadTransmissionFromKart(Pages::Menu* menu, PageId pageId, PushButton& button){
        if (!Pulsar::CupsConfig::IsRegsSituation() &&  VP::System::GetTransmission() == TRANSMISSION_DEFAULT){
            pageId = static_cast<PageId>(PAGE_TRANSMISSION_SELECT);
        }
        menu->LoadNextPageById(pageId, button);
    }
    kmCall(0x80846d2c, LoadTransmissionFromKart);
    kmCall(0x80846d64, LoadTransmissionFromKart);
    kmCall(0x80846e1c, LoadTransmissionFromKart);
    kmCall(0x80846e40, LoadTransmissionFromKart);

    static void LoadTransmissionFromDrift(Pages::Menu* menu, float delay){
        if (!Pulsar::CupsConfig::IsRegsSituation() && VP::System::GetTransmission() == TRANSMISSION_DEFAULT){
            menu->prevPageId = static_cast<PageId>(PAGE_TRANSMISSION_SELECT);
        }
        menu->LoadPrevPageWithDelay(delay);
    }
    kmBranch(0x8084e700, LoadTransmissionFromDrift);

    TransmissionSelect::TransmissionSelect(){
        nextPageId = PAGE_DRIFT_SELECT;
        prevPageId = PAGE_KART_SELECT;
        onButtonClickHandler.ptmf = &TransmissionSelect::OnButtonClick;
        onButtonSelectHandler.ptmf = &TransmissionSelect::OnButtonSelect;
        onBackPressHandler.ptmf = &TransmissionSelect::OnBackPress;
    }

    void TransmissionSelect::OnActivate(){
        for (int i = 0; i < this->externControlCount; i++){
            if (i == 0){
                this->externControls[i]->SetMessage(MENU_TRANSMISSION_INSIDE);
            }
            else if (i == 1){
                this->externControls[i]->SetMessage(MENU_TRANSMISSION_OUTSIDE);
            }
            else if (i == 2){
                this->externControls[i]->SetMessage(MENU_TRANSMISSION_HELP);
            }
        }
        this->titleBmg = MENU_TRANSMISSION_TITLE;
        MenuInteractable::OnActivate();
        PushButton& lastSelectedButton = *this->externControls[System::GetsInstance()->lastSelectedTransmissionId];
        this->SelectButton(lastSelectedButton);
        u32 buttonId = lastSelectedButton.buttonId;
        if (buttonId == 0){
            this->bottomText->SetMessage(MENU_TRANSMISSION_INSIDE_BOTTOM);
        }
        else if(buttonId == 1){
            this->bottomText->SetMessage(MENU_TRANSMISSION_OUTSIDE_BOTTOM);
        }
        else if(buttonId == 2){
            this->bottomText->SetMessage(MENU_TRANSMISSION_HELP_BOTTOM);
        }
    }

    void TransmissionSelect::SetButtonHandlers(PushButton& button){
        button.SetOnClickHandler(this->onButtonClickHandler, 0);
        button.SetOnSelectHandler(this->onButtonSelectHandler);
        button.SetOnDeselectHandler(this->onButtonDeselectHandler);
    }

    void TransmissionSelect::OnButtonClick(PushButton& button, u32 hudSlotId){
        System* vp = System::GetsInstance();
        switch (button.buttonId)
        {
            case 0:
                vp->transmissions[hudSlotId] = TRANSMISSION_INSIDE;
                vp->lastSelectedTransmission = TRANSMISSION_INSIDE;
                this->LoadNextPageById(PAGE_DRIFT_SELECT, button);
                break;
            case 1:
                vp->transmissions[hudSlotId] = TRANSMISSION_OUTSIDE;
                vp->lastSelectedTransmission = TRANSMISSION_OUTSIDE;
                this->LoadNextPageById(PAGE_DRIFT_SELECT, button);
                break;
            case 2:
                this->LoadMessageBoxTransparentPage(MENU_TRANSMISSION_HELP_DESC);
                break;
            default:
                break;
        }
        System::GetsInstance()->lastSelectedTransmissionId = button.buttonId;
    }

    void TransmissionSelect::OnButtonSelect(PushButton& button, u32 hudSlotId){
        u32 buttonId = button.buttonId;
        
        if (buttonId == 0){
            this->bottomText->SetMessage(MENU_TRANSMISSION_INSIDE_BOTTOM);
        }
        else if(buttonId == 1){
            this->bottomText->SetMessage(MENU_TRANSMISSION_OUTSIDE_BOTTOM);
        }
        else if(buttonId == 2){
            this->bottomText->SetMessage(MENU_TRANSMISSION_HELP_BOTTOM);
        }
    }

    void TransmissionSelect::OnBackPress(u32 hudSlotId){
        this->LoadPrevPageWithDelay(0.0f);
    }

    void TransmissionSelect::BeforeControlUpdate(){
        Pulsar::UI::ExpCharacterSelect* charSelect = SectionMgr::sInstance->curSection->Get<Pulsar::UI::ExpCharacterSelect>();
        if(charSelect->rouletteCounter != -1 && this->currentState == 0x4) {
            this->controlsManipulatorManager.inaccessible = true;
            Random random;
            PushButton* randomTransmission = this->externControls[random.NextLimited(2)];
            randomTransmission->HandleClick(0, -1);
        }
    }

    static void FixVehicleModelTransition(VehicleModelControl* ctrl, PageId id){
        if(id == static_cast<PageId>(PAGE_TRANSMISSION_SELECT)){
            id = PAGE_DRIFT_SELECT;
        }
        ctrl->SetAnimationType(id);
    };
    kmCall(0x80847678, FixVehicleModelTransition);
    kmCall(0x808476c8, FixVehicleModelTransition);

    // Disable DriftSelect Movies
    kmWrite32(0x8084e194, 0x60000000);

} // namespace UI
} // namespace VP