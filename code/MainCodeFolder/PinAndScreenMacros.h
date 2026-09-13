#ifndef PinAndScreenMacros
#define PinAndScreenMacros
#include <Arduino.h>

#define BUZZER_PIN 49 // Digital pin
// Following: https://www.instructables.com/ACTIVE-BUZZER-WITH-ARDUINO-UNO-R3/
#define JOYSTICK_XPIN A6
#define JOYSTICK_YPIN A7
#define JOYSTICK_BUTTON_PIN 48



// --- Touchscreen pin definitions ---
#define YP A3  // LCD_CS
#define XM A2  // LCD_CD
#define YM 9   // LCD_D1
#define XP 8   // LCD_D0
// --- Touchscreen calibration values (adjust as needed) ---
#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920
// ---- //
#define MINPRESSURE 100
#define MAXPRESSURE 1000
// 00000000000000000000000000 //
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// --- LCD control pins ---
#define LCD_CS A3
#define LCD_CD A2  // aka LCD_RS
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4  // !!
// 0000000000000000000000000000 //

#endif