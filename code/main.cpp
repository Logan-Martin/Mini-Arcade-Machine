#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>
#include <TouchScreen.h>

// CODE FOR JOYSTICK:
int xPin_Joystick = A6;
int yPin_Joystick = A7;

int buttonPin_Joystick = 48;
int xVal_Joystick;
int yVal_Joystick;
int buttonState_Joystick;
/// 000000000000000000 ///

// FOR BUTTONS:
const int buttonPinA = 32;
const int buttonPinB = 30;
int buttonAState = 0;
int buttonBState = 0;
/// 000000000000000000 ///

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
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
// 000000000000000000 //

// --- LCD control pins ---
#define LCD_CS A3
#define LCD_CD A2  // aka LCD_RS
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4  // !!

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


// --- Colors ---
#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define YELLOW 0xFFE0
// 000000000000000000 //
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
// 000000000000000000 //

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
  pinMode(xPin_Joystick, INPUT);
  pinMode(yPin_Joystick, INPUT);
  pinMode(buttonPin_Joystick, INPUT_PULLUP);
  // 00000000000000 //
  // FOR BUTTONS:
  pinMode(buttonPinA, INPUT_PULLUP);
  pinMode(buttonPinB, INPUT_PULLUP);
  // 0000000000000 //

  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(1);
  tft.fillScreen(BLUE);

  //tft.setTextColor(BLACK);
  tft.setTextSize(4);
  printWrappedText("Hello!", (SCREEN_WIDTH / 3.2) , SCREEN_HEIGHT / 3, 6, 6);

  tft.drawBitmap()

}

void Input() { // reads player inputs
  // JOYSTICK: //
  xVal_Joystick = analogRead(xPin_Joystick);
  yVal_Joystick = analogRead(yPin_Joystick);
  buttonState_Joystick = digitalRead(buttonPin_Joystick);

  // BUTTONS:
  buttonAState = digitalRead(buttonPinA);
  buttonBState = digitalRead(buttonPinB);
}

void Update() { // Move things [plr, enemy, etc] w/ math, enemy AI, or calculate physics

}

void Render() { // draw the graphics based on the Update changes
  if (buttonAState == LOW) {
    Serial.println("Pressed ButtonA!");
  }

  if (buttonBState == LOW) {
    Serial.println("Pressed ButtonB!");
  }
}


// --- Main loop ---
void loop() {
  Input(); 
  Update();
  Render();
}
