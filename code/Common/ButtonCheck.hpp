#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/Input/InputManager.hpp>
#include <game/Input/Controller.hpp>
#include <game/Input/ControllerHolder.hpp>
#include <kamek.hpp>

enum UniversalButtons{
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


enum Buttons {
  WHEEL_DPAD_LEFT = 0x1,
  WHEEL_DPAD_RIGHT = 0x2,
  WHEEL_DPAD_DOWN = 0x4,
  WHEEL_DPAD_UP = 0x8,
  WHEEL_A = 0x800,
  WHEEL_B = 0x400,
  WHEEL_MINUS = 0x1000,
  WHEEL_PLUS = 0x10,
  WHEEL_HOME = 0x8000,
  WHEEL_1 = 0x200,
  WHEEL_2 = 0x100,

  NUNCHUCK_DPAD_LEFT = 0x1,
  NUNCHUCK_DPAD_RIGHT = 0x2,
  NUNCHUCK_DPAD_DOWN = 0x4,
  NUNCHUCK_DPAD_UP = 0x8,
  NUNCHUCK_A = 0x800,
  NUNCHUCK_B = 0x400,
  NUNCHUCK_MINUS = 0x1000,
  NUNCHUCK_PLUS = 0x10,
  NUNCHUCK_HOME = 0x8000,
  NUNCHUCK_1 = 0x200,
  NUNCHUCK_2 = 0x100,
  NUNCHUCK_C = 0x4000,
  NUNCHUCK_Z = 0x2000,

  CLASSIC_DPAD_LEFT = 0x2,
  CLASSIC_DPAD_RIGHT = 0x2000,
  CLASSIC_DPAD_DOWN = 0x4000,
  CLASSIC_DPAD_UP = 0x1,
  CLASSIC_A = 0x10,
  CLASSIC_B = 0x40,
  CLASSIC_X = 0x8,
  CLASSIC_Y = 0x20,
  CLASSIC_MINUS = 0x1000,
  CLASSIC_PLUS = 0x40,
  CLASSIC_HOME = 0x800,
  CLASSIC_L = 0x2000,
  CLASSIC_R = 0x200,
  CLASSIC_ZL = 0x80,
  CLASSIC_Z = 0x4,

  GCN_DPAD_LEFT = 0x1,
  GCN_DPAD_RIGHT = 0x2,
  GCN_DPAD_DOWN = 0x4,
  GCN_DPAD_UP = 0x8,
  GCN_A = 0x100,
  GCN_B = 0x200,
  GCN_X = 0x400,
  GCN_Y = 0x800,
  GCN_Z = 0x10,
  GCN_START = 0x1000,
  GCN_L = 0x40,
  GCN_R = 0x20
};

bool CheckButtonPressed(Input::RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, u32 button);
bool CheckButtonCombination(Input::RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, UniversalButtons buttonMask);