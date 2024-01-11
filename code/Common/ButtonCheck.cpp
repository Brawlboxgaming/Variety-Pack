#include <Common/ButtonCheck.hpp>
#include <core/rvl/os/OS.hpp>

bool CheckButton(Buttons specific, u16 inputs){
    return (inputs & specific) != 0;
}

bool CheckButtonPressed(Input::RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, u32 button){
    u16 inputs = controllerHolder->inputStates[0].buttonRaw;
    if (onlyCheckNewButtons) inputs = (inputs & ~controllerHolder->inputStates[1].buttonRaw);

    float horizontalCStick;
    float verticalCStick;
    if (controllerType == WHEEL){
        switch (button){
            case BUTTON_DPAD_LEFT: return CheckButton(WHEEL_DPAD_LEFT, inputs);
            case BUTTON_DPAD_RIGHT: return CheckButton(WHEEL_DPAD_RIGHT, inputs);
            case BUTTON_DPAD_DOWN: return CheckButton(WHEEL_DPAD_DOWN, inputs);
            case BUTTON_DPAD_UP: return CheckButton(WHEEL_DPAD_UP, inputs);
            case BUTTON_A: return CheckButton(WHEEL_A, inputs);
            case BUTTON_B: return CheckButton(WHEEL_B, inputs);
            case BUTTON_MINUS: return CheckButton(WHEEL_MINUS, inputs);
            case BUTTON_PLUS: return CheckButton(WHEEL_PLUS, inputs);
            case BUTTON_HOME: return CheckButton(WHEEL_HOME, inputs);
            case BUTTON_1: return CheckButton(WHEEL_1, inputs);
            case BUTTON_2: return CheckButton(WHEEL_2, inputs);
            default: return false;
        }
    }
    else if (controllerType == NUNCHUCK){
        switch (button){
            case BUTTON_DPAD_LEFT: return CheckButton(NUNCHUCK_DPAD_LEFT, inputs);
            case BUTTON_DPAD_RIGHT: return CheckButton(NUNCHUCK_DPAD_RIGHT, inputs);
            case BUTTON_DPAD_DOWN: return CheckButton(NUNCHUCK_DPAD_DOWN, inputs);
            case BUTTON_DPAD_UP: return CheckButton(NUNCHUCK_DPAD_UP, inputs);
            case BUTTON_A: return CheckButton(NUNCHUCK_A, inputs);
            case BUTTON_B: return CheckButton(NUNCHUCK_B, inputs);
            case BUTTON_MINUS: return CheckButton(NUNCHUCK_MINUS, inputs);
            case BUTTON_PLUS: return CheckButton(NUNCHUCK_PLUS, inputs);
            case BUTTON_HOME: return CheckButton(NUNCHUCK_HOME, inputs);
            case BUTTON_1: return CheckButton(NUNCHUCK_1, inputs);
            case BUTTON_2: return CheckButton(NUNCHUCK_2, inputs);
            case BUTTON_C: return CheckButton(NUNCHUCK_C, inputs);
            case BUTTON_Z: return CheckButton(NUNCHUCK_Z, inputs);
            default: return false;
        }
        
    }
    else if (controllerType == CLASSIC){
        Input::WiiController *wiiController = (Input::WiiController*) controllerHolder->curController;
        horizontalCStick = wiiController->kpadStatus[0].extStatus.cl.stickR.x;
        verticalCStick = wiiController->kpadStatus[0].extStatus.cl.stickR.y;
        switch (button){
            case BUTTON_DPAD_LEFT: return CheckButton(CLASSIC_DPAD_LEFT, inputs);
            case BUTTON_DPAD_RIGHT: return CheckButton(CLASSIC_DPAD_RIGHT, inputs) || CheckButton(CLASSIC_L, inputs);
            case BUTTON_DPAD_DOWN: return CheckButton(CLASSIC_DPAD_DOWN, inputs);
            case BUTTON_DPAD_UP: return CheckButton(CLASSIC_DPAD_UP, inputs);
            case BUTTON_A: return CheckButton(CLASSIC_A, inputs);
            case BUTTON_B: return CheckButton(CLASSIC_B, inputs) || CheckButton(CLASSIC_PLUS, inputs);
            case BUTTON_X: return CheckButton(CLASSIC_X, inputs);
            case BUTTON_Y: return CheckButton(CLASSIC_Y, inputs);
            case BUTTON_MINUS: return CheckButton(CLASSIC_MINUS, inputs);
            case BUTTON_HOME: return CheckButton(CLASSIC_HOME, inputs);
            case BUTTON_R: return CheckButton(CLASSIC_R, inputs);
            case BUTTON_ZL: return CheckButton(CLASSIC_ZL, inputs);
            case BUTTON_Z: return CheckButton(CLASSIC_Z, inputs);
            default: return false;
        }
    }
    else{
        // Doesn't work
        Input::GCNController *gcnController = (Input::GCNController*) controllerHolder->curController;
        horizontalCStick = gcnController->padStatus.cStickX;
        verticalCStick = gcnController->padStatus.cStickY;
        switch (button){
            case BUTTON_DPAD_LEFT: return CheckButton(GCN_DPAD_LEFT, inputs);
            case BUTTON_DPAD_RIGHT: return CheckButton(GCN_DPAD_RIGHT, inputs);
            case BUTTON_DPAD_DOWN: return CheckButton(GCN_DPAD_DOWN, inputs);
            case BUTTON_DPAD_UP: return CheckButton(GCN_DPAD_UP, inputs);
            case BUTTON_A: return CheckButton(GCN_A, inputs);
            case BUTTON_B: return CheckButton(GCN_B, inputs);
            case BUTTON_X: return CheckButton(GCN_X, inputs);
            case BUTTON_Y: return CheckButton(GCN_Y, inputs);
            case BUTTON_Z: return CheckButton(GCN_Z, inputs);
            case BUTTON_PLUS: return CheckButton(GCN_START, inputs);
            case BUTTON_L: return CheckButton(GCN_L, inputs);
            case BUTTON_R: return CheckButton(GCN_R, inputs);
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

bool CheckButtonCombination(Input::RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, UniversalButtons buttonMask){
    bool pressed = true;
    for (int i = 0; i < 32; ++i) {
        int iMask = 1 << i;
        if (buttonMask & iMask)
            if (!CheckButtonPressed(controllerHolder, controllerType, onlyCheckNewButtons, (UniversalButtons) iMask)) pressed = false;
        }
    return pressed;
}