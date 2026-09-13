#ifndef InputStructs
#define InputStructs
#include <Arduino.h>
#include "PinAndScreenMacros.h"

struct JoystickStruct {
  int xPin = JOYSTICK_XPIN;
  int yPin = JOYSTICK_YPIN;
  
  int xVal;
  int yVal;
  //
  int MAX_TOTAL_read_val = 1008;
  int MIN_TOTAL_read_val = 70;
  int CENTER_REST_READ_VAL = 504;
  float deadzone = 1.29;
  
  int UP_Req_Read_For_Movement;
  int DOWN_Req_Read_For_Movement;
  //

  int buttonPin = JOYSTICK_BUTTON_PIN;
  bool buttonState;
  bool buttonDebounce = false;
};

struct PushbuttonStruct {
  int buttonPin;
  bool buttonState;
  bool buttonDebounce;
};

#endif