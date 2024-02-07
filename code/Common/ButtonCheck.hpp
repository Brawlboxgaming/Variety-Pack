#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/Input/InputManager.hpp>
#include <MarioKartWii/Input/Controller.hpp>
#include <MarioKartWii/Input/ControllerHolder.hpp>
#include <core/rvl/WPAD.hpp>
#include <core/rvl/PAD.hpp>
#include <kamek.hpp>

namespace VP {
namespace Button {
enum Universal{
  BUTTON_NONE             = 0,
  BUTTON_DPAD_LEFT        = 1 << 0,
  BUTTON_DPAD_RIGHT       = 1 << 1,
  BUTTON_DPAD_DOWN        = 1 << 2,
  BUTTON_DPAD_UP          = 1 << 3,
  BUTTON_A                = 1 << 4,
  BUTTON_B                = 1 << 5,
  BUTTON_X                = 1 << 6,
  BUTTON_Y                = 1 << 7,
  BUTTON_MINUS            = 1 << 8,
  BUTTON_PLUS             = 1 << 9,
  BUTTON_HOME             = 1 << 10,
  BUTTON_1                = 1 << 11,
  BUTTON_2                = 1 << 12,
  BUTTON_L                = 1 << 13,
  BUTTON_R                = 1 << 14,
  BUTTON_C                = 1 << 15,
  BUTTON_Z                = 1 << 16,
  BUTTON_ZL               = 1 << 17,
  C_STICK_UP_EIGHT        = 1 << 18,
  C_STICK_UPRIGHT_EIGHT   = 1 << 19,
  C_STICK_RIGHT_EIGHT     = 1 << 20,
  C_STICK_DOWNRIGHT_EIGHT = 1 << 21,
  C_STICK_DOWN_EIGHT      = 1 << 22,
  C_STICK_DOWNLEFT_EIGHT  = 1 << 23,
  C_STICK_LEFT_EIGHT      = 1 << 24,
  C_STICK_UPLEFT_EIGHT    = 1 << 25,
};

bool CheckPressed(Input::RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, u32 button);
bool CheckCombination(Input::RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, Universal buttonMask);
} // namespace Button
} // namespace VP