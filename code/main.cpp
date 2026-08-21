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
unsigned long lastTime = 0; // stamp for deltaTime calculation
// 0000000000000000000 //

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

struct TriangleData {
  int16_t x0; 
  int16_t y0; 

  int16_t x1; 
  int16_t y1; 

  int16_t x2; 
  int16_t y2;

  uint16_t color;
};

struct JoystickStruct {
  int xPin = A6;
  int yPin = A7;
  
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

  int buttonPin = 48;
  bool buttonState;
  bool buttonDebounce = false;
};
JoystickStruct joystick;

struct PushbuttonStruct {
  int buttonPin;
  bool buttonState;
  bool buttonDebounce;
};
PushbuttonStruct ButtonA = {32, false, false};
PushbuttonStruct ButtonB = {30, false, false};

struct CharacterStruct {
  int xPos = 0;
  int yPos = 0;
  
  byte health = 1;  // 1 to 255
  byte walkSpeed = 75; // 1 to 255

  byte type = 1; // could add a type based on numbers. like 1 = player, 2 = enemy
  int score = 0;
};
CharacterStruct Player; 
CircleData PlayerCircle;

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
  joystick.UP_Req_Read_For_Movement = joystick.deadzone * joystick.CENTER_REST_READ_VAL;
  joystick.DOWN_Req_Read_For_Movement = (joystick.CENTER_REST_READ_VAL - (joystick.UP_Req_Read_For_Movement - joystick.CENTER_REST_READ_VAL));
  //
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

  //tft.fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)

  Player.xPos = (SCREEN_WIDTH / 2);
  Player.yPos = (SCREEN_HEIGHT / 2);
  tft.fillCircle(Player.xPos, Player.yPos, PlayerCircle.radius , PlayerCircle.color);
  //PlayerCircle.color = BLACK;
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

void Update(float deltaTime) { // Move things [plr, enemy, etc] w/ math, enemy AI, or calculate physics
  bool xCondition_RIGHT  = (joystick.xVal >= joystick.UP_Req_Read_For_Movement); // X Right Cond.
  bool yCondition_UP  = (joystick.yVal >= joystick.UP_Req_Read_For_Movement); // Y Up Cond.
  bool xCondition_LEFT  = (joystick.xVal <= joystick.DOWN_Req_Read_For_Movement); // X LEFT Cond.
  bool yCondition_DOWN  = (joystick.yVal <= joystick.DOWN_Req_Read_For_Movement); // Y DOWN Cond.

  Serial.print("DEADZONE: ");
  Serial.print(joystick.CENTER_REST_READ_VAL * joystick.deadzone);
  Serial.print("| X Read: ");
  Serial.print(joystick.xVal);
  Serial.print("| Y Read: ");
  Serial.print(joystick.yVal);
  Serial.println();

  if (xCondition_RIGHT || xCondition_LEFT || yCondition_UP || yCondition_DOWN ) { // if past deadzone
    // UP -> Y up, Down -> Y down
    // Left -> X up, Right -> X down
    float totalRange = (float)(joystick.MAX_TOTAL_read_val - joystick.MIN_TOTAL_read_val);
    float xDirection = (((float)joystick.xVal - joystick.MIN_TOTAL_read_val ) / (totalRange / 2.0f)) - 1.0f;
    float yDirection = (((float)joystick.yVal - joystick.MIN_TOTAL_read_val) / (totalRange / 2.0f)) - 1.0f;

    Player.xPos += (-xDirection * Player.walkSpeed * deltaTime);
    Player.yPos += (-yDirection * Player.walkSpeed * deltaTime);
  }
  // Printing:
  //Serial.print("X: ");
  //Serial.print(joystick.xVal);
  //Serial.print("| Y: ");
  //Serial.print(joystick.yVal);
  //Serial.println();
}

void Render(float deltaTime) { // draw the graphics based on the Update changes
  // get rid of old plr spot://
  tft.fillCircle(PlayerCircle.xPos, PlayerCircle.yPos, PlayerCircle.radius , BLUE);
  // Updated plr position:
  PlayerCircle.xPos = Player.xPos;
  PlayerCircle.yPos = Player.yPos;
  tft.fillCircle(PlayerCircle.xPos, PlayerCircle.yPos, PlayerCircle.radius , PlayerCircle.color);

  // Probably want to render things in different steps.
  // Player
  // Enemies
  // UI [last so it's on top]
  // Pause or Game Over UI [so it's on top Score UI]

  // BUTTONS: //
  if (ButtonA.buttonState == LOW && ButtonA.buttonDebounce == false) {
    //ButtonA.buttonDebounce = true; 
    tft.fillCircle(SCREEN_WIDTH - (CircleA.radius * 1.5), SCREEN_HEIGHT - (CircleA.radius * 1.5) - 60, CircleA.radius, RED);
    //Player.score -= 1;
  }
  else { // i need a stopgap / Debounce for this
    //ButtonA.buttonDebounce = false; 
    tft.fillCircle(SCREEN_WIDTH - (CircleA.radius * 1.5), SCREEN_HEIGHT - (CircleA.radius * 1.5) - 60, CircleA.radius, BLACK);
  }

  if (ButtonB.buttonState == LOW && ButtonB.buttonDebounce == false) {
    //ButtonB.buttonDebounce = true; 
    tft.fillCircle(SCREEN_WIDTH - (CircleB.radius * 1.5), SCREEN_HEIGHT - (CircleB.radius * 1.5), CircleB.radius, GREEN);
    //Player.score += 1;
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


  // UI Score:
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  //String scoreStr = ("Score: " + String(Player.score)); // DON'T DO THIS EVERY FRAME! allocate a char[16]. 16 can be any number. What do would use then in games idk.
  //const char* c_Based_ScoreStr = scoreStr.c_str(); 
  printWrappedText("Score: 0", ((SCREEN_WIDTH / SCREEN_WIDTH) + 5) , ((SCREEN_HEIGHT / SCREEN_HEIGHT) + 5) , 16, 1);
  // 00000 //
}


// --- Main loop ---
void loop() {
  // setup function above already run by default with Arduino
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  Input(); 
  Update(deltaTime);
  Render(deltaTime);
  // I'm using flash memory so it wipes each upload.
  // If I needto store data, like a highscore, then I'd need to store that and possibly clean up that if need-be.
}
