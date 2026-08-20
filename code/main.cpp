#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>
#include <TouchScreen.h>

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

struct CircleData {
  int16_t xPos = 0;
  int16_t yPos = 0;
  int16_t radius = 20;
  uint16_t color = BLACK;
  bool drawDebounce = false;
};
CircleData CircleA;
CircleData CircleB;
CircleData Circle_JoystickButton;

struct JoystickStruct {
  int xPin = A6;
  int yPin = A7;
  
  int xVal;
  int yVal;

  int buttonPin = 48;
  int buttonState;
  int buttonDebounce = 0;
};
JoystickStruct joystick;

struct PushbuttonStruct {
  int buttonPin;
  int buttonState;
  int buttonDebounce;
};
PushbuttonStruct ButtonA = {32, 0, 0};
PushbuttonStruct ButtonB = {30, 0, 0};



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
  pinMode(joystick.xPin, INPUT);
  pinMode(joystick.yPin, INPUT);
  pinMode(joystick.buttonPin , INPUT_PULLUP);
  // 00000000000000 //

  // FOR BUTTONS:
  pinMode(ButtonA.buttonPin, INPUT_PULLUP);
  pinMode(ButtonB.buttonPin, INPUT_PULLUP);
  // 0000000000000 //

  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(1);
  tft.fillScreen(BLUE);

  //tft.setTextColor(BLACK);
  tft.setTextSize(4);
  printWrappedText("Hello!", (SCREEN_WIDTH / 3.2) , SCREEN_HEIGHT / 3, 6, 6);

  // 000 - On-Screen Button indicators - 000 ///
  //tft.fillCircle(SCREEN_WIDTH - (CircleA.radius * 1.5), SCREEN_HEIGHT - (CircleA.radius * 1.5) - 60, CircleA.radius, BLACK);
  //tft.fillCircle(SCREEN_WIDTH - (CircleB.radius * 1.5), SCREEN_HEIGHT - (CircleB.radius * 1.5), CircleB.radius, BLACK);
  //tft.fillCircle(Circle_JoystickButton.radius * 1.5, SCREEN_HEIGHT - (Circle_JoystickButton.radius * 1.5), Circle_JoystickButton.radius, BLACK);
  // 00000 //
}

void Input() { // reads player inputs
  // JOYSTICK: //
  joystick.xVal = analogRead(joystick.xPin);
  joystick.yVal = analogRead(joystick.yPin);
  joystick.buttonState = digitalRead(joystick.buttonPin);

  // BUTTONS:
  ButtonA.buttonState = digitalRead(ButtonA.buttonPin);
  ButtonB.buttonState = digitalRead(ButtonB.buttonPin);
}

void Update() { // Move things [plr, enemy, etc] w/ math, enemy AI, or calculate physics

}

void Render() { // draw the graphics based on the Update changes
  if (ButtonA.buttonState == LOW && ButtonA.buttonDebounce == false) {
    //ButtonA.buttonDebounce = true; 
    tft.fillCircle(SCREEN_WIDTH - (CircleA.radius * 1.5), SCREEN_HEIGHT - (CircleA.radius * 1.5) - 60, CircleA.radius, RED);
  }
  else { // i need a stopgap / Debounce for this
    //ButtonA.buttonDebounce = false; 
    tft.fillCircle(SCREEN_WIDTH - (CircleA.radius * 1.5), SCREEN_HEIGHT - (CircleA.radius * 1.5) - 60, CircleA.radius, BLACK);
  }

  if (ButtonB.buttonState == LOW && ButtonB.buttonDebounce == false) {
    //ButtonB.buttonDebounce = true; 
    tft.fillCircle(SCREEN_WIDTH - (CircleB.radius * 1.5), SCREEN_HEIGHT - (CircleB.radius * 1.5), CircleB.radius, GREEN);
  }
  else { // i need a stopgap / Debounce for this
    //ButtonB.buttonDebounce = false; 
    tft.fillCircle(SCREEN_WIDTH - (CircleB.radius * 1.5), SCREEN_HEIGHT - (CircleB.radius * 1.5), CircleB.radius, BLACK);
  }

  if (joystick.buttonState == LOW && joystick.buttonDebounce == false) {
    //joystick.buttonDebounce = true;
    tft.fillCircle(Circle_JoystickButton.radius * 1.5, SCREEN_HEIGHT - (Circle_JoystickButton.radius * 1.5), Circle_JoystickButton.radius, YELLOW);
  }
  else { // i need a stopgap / Debounce for this
    //joystick.buttonDebounce = false;
    tft.fillCircle(Circle_JoystickButton.radius * 1.5, SCREEN_HEIGHT - (Circle_JoystickButton.radius * 1.5), Circle_JoystickButton.radius, BLACK);
  }
}


// --- Main loop ---
void loop() {
  // setup function above already run by default with Arduino

  Input(); 
  Update();
  Render();

  // I'm using flash memory so it wipes each upload.
  // If I needto store data, like a highscore, then I'd need to store that and possibly clean up that if need-be.
}
