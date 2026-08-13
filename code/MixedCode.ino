#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>
#include <TouchScreen.h>

// ------------ //
// CODE FOR JOYSTICK:
int xPin = A6;
int yPin = A7;

int buttonPin = 52;
int xVal;
int yVal;
int buttonState;
/// ---------------- ///
// FOR BUTTONS:
const int buttonPinA = 48; 
const int buttonPinB = 50; 
int buttonAState = 0; 
int buttonBState = 0; 
/// 000000000000000000 ///




// --- Touchscreen pin definitions ---
#define YP A3 // LCD_CS
#define XM A2 // LCD_CD
#define YM 9 // LCD_D1
#define XP 8 // LCD_D0

// --- Touchscreen calibration values (adjust as needed) ---
#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

#define MINPRESSURE 100
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// --- LCD control pins ---
#define LCD_CS A3 
#define LCD_CD A2 // aka LCD_RS
#define LCD_WR A1 
#define LCD_RD A0
#define LCD_RESET A4 // !!

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// --- Colors ---
#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define YELLOW 0xFFE0

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240


// --- Text wrapping ---
void printWrappedText(const char* text, int x, int y, int maxWidthChars, int lineHeight) {
 tft.setCursor(x, y);
 char tempText[256];
 strcpy(tempText, text);
 char* rest = tempText;
 char* word;
 String line = "";
 
 while ((word = strtok_r(rest, " ", &rest))) {
 if (line.length() + strlen(word) + (line.length() > 0 ? 1 : 0) > maxWidthChars) {
 tft.print(line);
 y += lineHeight;
 tft.setCursor(x, y);
 line = word;
 line += " ";
 } else {
 line += word;
 line += " ";
 }
 }
 if (line.length() > 0) {
 tft.print(line);
 }
}

// --- Setup ---
void setup() {
 Serial.begin(9600);
 randomSeed(analogRead(0));

// FOR JOYSTICK:
 pinMode(xPin, INPUT);
 pinMode(yPin, INPUT);
 pinMode(buttonPin, INPUT_PULLUP);
// 00000000000000 //
// FOR BUTTONS:
 pinMode(buttonPinA, INPUT_PULLUP);
 pinMode(buttonPinB, INPUT_PULLUP);
// 0000000000000 //

 tft.reset();
 tft.begin(0x9341);
 tft.setRotation(1);
 tft.fillScreen(RED);
}

// --- Main loop ---
void loop() {
    // JOYSTICK: //
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  buttonState = digitalRead(buttonPin);

  // BUTTONS:
  buttonAState = digitalRead(buttonPinA);
  buttonBState = digitalRead(buttonPinB);

  if (buttonAState == LOW) {
    Serial.println("Pressed ButtonA!");
  }

  if (buttonBState == LOW) {
    Serial.println("Pressed ButtonB!");
  }

  // Printing:
  Serial.print("X: ");
  Serial.print(xVal);
  Serial.print("| Y: ");
  Serial.print(yVal);
  Serial.print("| Button: ");
  Serial.print(buttonState);
  Serial.println();
  // 000000000 //
}
