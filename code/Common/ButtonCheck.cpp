#include <Common/ButtonCheck.hpp>
#include <core/rvl/os/OS.hpp>

namespace VP {
namespace Button {
bool Check(u32 specific, u16 inputs){
    return (inputs & specific) != 0;
}

bool CheckPressed(Input::RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, u32 button){
    u16 inputs = controllerHolder->inputStates[0].buttonRaw;
    if (onlyCheckNewButtons) inputs = (inputs & ~controllerHolder->inputStates[1].buttonRaw);

    float horizontalCStick;
    float verticalCStick;
    if (controllerType == WHEEL){
        switch (button){
            case BUTTON_DPAD_LEFT: return Check(WPAD::WPAD_BUTTON_LEFT, inputs);
            case BUTTON_DPAD_RIGHT: return Check(WPAD::WPAD_BUTTON_RIGHT, inputs);
            case BUTTON_DPAD_DOWN: return Check(WPAD::WPAD_BUTTON_DOWN, inputs);
            case BUTTON_DPAD_UP: return Check(WPAD::WPAD_BUTTON_UP, inputs);
            case BUTTON_A: return Check(WPAD::WPAD_BUTTON_A, inputs);
            case BUTTON_B: return Check(WPAD::WPAD_BUTTON_B, inputs);
            case BUTTON_MINUS: return Check(WPAD::WPAD_BUTTON_MINUS, inputs);
            case BUTTON_PLUS: return Check(WPAD::WPAD_BUTTON_PLUS, inputs);
            case BUTTON_HOME: return Check(WPAD::WPAD_BUTTON_HOME, inputs);
            case BUTTON_1: return Check(WPAD::WPAD_BUTTON_1, inputs);
            case BUTTON_2: return Check(WPAD::WPAD_BUTTON_2, inputs);
            default: return false;
        }
    }
    else if (controllerType == NUNCHUCK){
        switch (button){
            case BUTTON_DPAD_LEFT: return Check(WPAD::WPAD_BUTTON_LEFT, inputs);
            case BUTTON_DPAD_RIGHT: return Check(WPAD::WPAD_BUTTON_RIGHT, inputs);
            case BUTTON_DPAD_DOWN: return Check(WPAD::WPAD_BUTTON_DOWN, inputs);
            case BUTTON_DPAD_UP: return Check(WPAD::WPAD_BUTTON_UP, inputs);
            case BUTTON_A: return Check(WPAD::WPAD_BUTTON_A, inputs);
            case BUTTON_B: return Check(WPAD::WPAD_BUTTON_B, inputs);
            case BUTTON_MINUS: return Check(WPAD::WPAD_BUTTON_MINUS, inputs);
            case BUTTON_PLUS: return Check(WPAD::WPAD_BUTTON_PLUS, inputs);
            case BUTTON_HOME: return Check(WPAD::WPAD_BUTTON_HOME, inputs);
            case BUTTON_1: return Check(WPAD::WPAD_BUTTON_1, inputs);
            case BUTTON_2: return Check(WPAD::WPAD_BUTTON_2, inputs);
            case BUTTON_C: return Check(WPAD::WPAD_BUTTON_C, inputs);
            case BUTTON_Z: return Check(WPAD::WPAD_BUTTON_Z, inputs);
            default: return false;
        }
        
    }
    else if (controllerType == CLASSIC){
        Input::WiiController *wiiController = static_cast<Input::WiiController*>(controllerHolder->curController);
        horizontalCStick = wiiController->kpadStatus[0].extStatus.cl.stickR.x;
        verticalCStick = wiiController->kpadStatus[0].extStatus.cl.stickR.y;
        switch (button){
            case BUTTON_DPAD_LEFT: return Check(WPAD::WPAD_CL_BUTTON_LEFT, inputs);
            case BUTTON_DPAD_RIGHT: return Check(WPAD::WPAD_CL_BUTTON_RIGHT, inputs) || Check(WPAD::WPAD_CL_TRIGGER_L, inputs);
            case BUTTON_DPAD_DOWN: return Check(WPAD::WPAD_CL_BUTTON_DOWN, inputs);
            case BUTTON_DPAD_UP: return Check(WPAD::WPAD_CL_BUTTON_UP, inputs);
            case BUTTON_A: return Check(WPAD::WPAD_CL_BUTTON_A, inputs);
            case BUTTON_B: return Check(WPAD::WPAD_CL_BUTTON_B, inputs) || Check(WPAD::WPAD_CL_BUTTON_PLUS, inputs);
            case BUTTON_X: return Check(WPAD::WPAD_CL_BUTTON_X, inputs);
            case BUTTON_Y: return Check(WPAD::WPAD_CL_BUTTON_Y, inputs);
            case BUTTON_MINUS: return Check(WPAD::WPAD_CL_BUTTON_MINUS, inputs);
            case BUTTON_HOME: return Check(WPAD::WPAD_CL_BUTTON_HOME, inputs);
            case BUTTON_R: return Check(WPAD::WPAD_CL_TRIGGER_R, inputs);
            case BUTTON_ZL: return Check(WPAD::WPAD_CL_TRIGGER_ZL, inputs);
            case BUTTON_Z: return Check(WPAD::WPAD_CL_TRIGGER_ZR, inputs);
            default: return false;
        }
    }
    else{
        Input::GCNController *gcnController = static_cast<Input::GCNController*>(controllerHolder->curController);
        horizontalCStick = gcnController->padStatus.cStickX;
        verticalCStick = gcnController->padStatus.cStickY;
        switch (button){
            case BUTTON_DPAD_LEFT: return Check(PAD::PAD_BUTTON_LEFT, inputs);
            case BUTTON_DPAD_RIGHT: return Check(PAD::PAD_BUTTON_RIGHT, inputs);
            case BUTTON_DPAD_DOWN: return Check(PAD::PAD_BUTTON_DOWN, inputs);
            case BUTTON_DPAD_UP: return Check(PAD::PAD_BUTTON_UP, inputs);
            case BUTTON_A: return Check(PAD::PAD_BUTTON_A, inputs);
            case BUTTON_B: return Check(PAD::PAD_BUTTON_B, inputs);
            case BUTTON_X: return Check(PAD::PAD_BUTTON_X, inputs);
            case BUTTON_Y: return Check(PAD::PAD_BUTTON_Y, inputs);
            case BUTTON_Z: return Check(PAD::PAD_BUTTON_Z, inputs);
            case BUTTON_PLUS: return Check(PAD::PAD_BUTTON_START, inputs);
            case BUTTON_L: return Check(PAD::PAD_BUTTON_L, inputs);
            case BUTTON_R: return Check(PAD::PAD_BUTTON_R, inputs);
            default: return false;
        }
    }
    if (button >= C_STICK_UP_EIGHT && button <= C_STICK_UPLEFT_EIGHT){
        const float const1 = 0.92387953251;
        const float const2 = 0.38268343236;
        switch (button){
            case(C_STICK_UP_EIGHT): return (verticalCStick >= const1);
            case(C_STICK_UPRIGHT_EIGHT): return (verticalCStick >=const2 && horizontalCStick >= const2);
            case(C_STICK_RIGHT_EIGHT): return (horizontalCStick >= const1);
            case(C_STICK_DOWNRIGHT_EIGHT): return (verticalCStick <= -const2 && horizontalCStick >= const2);
            case(C_STICK_DOWN_EIGHT): return (verticalCStick <= -const1);
            case(C_STICK_DOWNLEFT_EIGHT): return (verticalCStick <= -const2 && horizontalCStick <= -const2);
            case(C_STICK_LEFT_EIGHT): return (horizontalCStick <= -const1);
            case(C_STICK_UPLEFT_EIGHT): return (verticalCStick >=const2 && horizontalCStick <= -const2);
        }
    }
    return false;
}

bool CheckCombination(Input::RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, Universal buttonMask){
    bool pressed = true;
    for (int i = 0; i < 32; ++i) {
        int iMask = 1 << i;
        if (buttonMask & iMask)
            if (!CheckPressed(controllerHolder, controllerType, onlyCheckNewButtons, static_cast<Universal>(iMask))) pressed = false;
        }
    return pressed;
}
} // namespace Button
} // namespace VP