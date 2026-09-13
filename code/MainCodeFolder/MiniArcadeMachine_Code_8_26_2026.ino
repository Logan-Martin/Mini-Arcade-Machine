#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>
#include <TouchScreen.h>
// Custom:
#include "CustShapes.h" // Circle, Triangle, Square
#include "CustomColors.h"
#include "InputStructs.h"
#include "PinAndScreenMacros.h"
#include "BulletStruct.h"
#include "Character.h"
#include "PrintWrappedTextHelper.h"

// 000000000000000000 // 
// NOTE: Macros/Variables for these in "PinAndScreenMacros.h"
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// 000000000000000000 //

unsigned long lastTime = 0; // stamp for deltaTime calculation
// 0000000000000000000 //

bool SoundEnabled = false;
void PlayAudioChirp(int delayTime) { // 50 is too much, 10 is eh
  if (SoundEnabled) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(delayTime);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

// For On-Screen Button Representation:
CircleData CircleA;
CircleData CircleB;
CircleData Circle_JoystickButton;

// Actual Button Structs:
PushbuttonStruct ButtonA = {32, false, false};
PushbuttonStruct ButtonB = {30, false, false};
JoystickStruct joystick;

// ---- //
CharacterStruct Player; 
CharacterStruct enemyList[1];

Bullet listOfBullets[8];
int sizeOfBulletList = 8;
// 00000000000000000000000000 //


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
  pinMode(BUZZER_PIN,OUTPUT);
  // 000000 //

  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(1);
  tft.fillScreen(BACKGROUND_COLOR);



  // 000000000 //
  SetUpCharacter(&Player, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, BLUE, nullptr);
  fillTriangle_Helper_CHAR(&Player, NULL);
  // 0000000000 //

  struct TriangleData enemyTriRelationshipData;
  enemyTriRelationshipData.x0 = 0;
  enemyTriRelationshipData.y0 = 0;
  enemyTriRelationshipData.x1 = -15;
  enemyTriRelationshipData.y1 = -15;
  enemyTriRelationshipData.x2 = -30;
  enemyTriRelationshipData.y2 = 0;

  CharacterStruct Enemy1;
  SetUpCharacter(&Enemy1, SCREEN_WIDTH/2, SCREEN_HEIGHT/3.5, RED, &enemyTriRelationshipData);
  fillTriangle_Helper_CHAR(&Enemy1, NULL);

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
    
    float tempXChange = (-xDirection * Player.walkSpeed * deltaTime);
    float tempYChange = (-yDirection * Player.walkSpeed * deltaTime);

    UpdateTrianglePoints(Player.triangleData , tempXChange, tempYChange);
  }
}

void Render(float deltaTime) { // draw the graphics based on the Update changes
  // flicker: https://forum.pjrc.com/index.php?threads/anyway-to-stop-flickering-during-update-on-ili9341-display.59926/
  // It's a timing? issue. Maybe add frame buffer.
  
  fillTriangle_Helper_CHAR(&Player, NULL);
  fillTriangle_Helper_CHAR(&Player, NULL);
  fillTriangle_Helper_CHAR(&Player, NULL);
  fillTriangle_Helper_CHAR(&Player, NULL);
  fillTriangle_Helper_CHAR(&Player, NULL);
  fillTriangle_Helper_CHAR(&Player, NULL);
  //delayMicroseconds(deltaTime);
  fillTriangle_Helper_CHAR(&Player, BACKGROUND_COLOR);

  // Probably want to render things in different steps.
  // Player
  // Enemies
  // UI [last so it's on top]
  // Pause or Game Over UI [so it's on top Score UI]

  // BUTTONS: //
  if (ButtonA.buttonState == LOW && ButtonA.buttonDebounce == false) {
    //ButtonA.buttonDebounce = true; 
    tft.fillCircle(SCREEN_WIDTH - (CircleA.radius * 1.5), SCREEN_HEIGHT - (CircleA.radius * 1.5) - 60, CircleA.radius, RED);
    PlayAudioChirp(25);

    Bullet bullet_Clone;
    bullet_Clone.lineData.pointA.xPos = Player.triangleData.x1;
    bullet_Clone.lineData.pointA.yPos = Player.triangleData.y1;
    SetPointB_OfLine_BasedOnLength_And_PointA(bullet_Clone.lineData, 10);
    tft.drawLine(bullet_Clone.lineData.pointA.xPos, bullet_Clone.lineData.pointA.yPos, bullet_Clone.lineData.pointB.xPos, bullet_Clone.lineData.pointB.yPos, RED);

    //Player.score -= 1;
  }
  else { // i need a stopgap / Debounce for this
    //ButtonA.buttonDebounce = false; 
    tft.fillCircle(SCREEN_WIDTH - (CircleA.radius * 1.5), SCREEN_HEIGHT - (CircleA.radius * 1.5) - 60, CircleA.radius, GRAY);
    digitalWrite(BUZZER_PIN,LOW);
  };

  if (ButtonB.buttonState == LOW && ButtonB.buttonDebounce == false) {
    //ButtonB.buttonDebounce = true; 
    tft.fillCircle(SCREEN_WIDTH - (CircleB.radius * 1.5), SCREEN_HEIGHT - (CircleB.radius * 1.5), CircleB.radius, GREEN);
    //Player.score += 1;
  }
  else { // i need a stopgap / Debounce for this
    //ButtonB.buttonDebounce = false; 
    tft.fillCircle(SCREEN_WIDTH - (CircleB.radius * 1.5), SCREEN_HEIGHT - (CircleB.radius * 1.5), CircleB.radius, GRAY);
  };

  if (joystick.buttonState == LOW && joystick.buttonDebounce == false) {
    //joystick.buttonDebounce = true;
    tft.fillCircle(Circle_JoystickButton.radius * 1.5, SCREEN_HEIGHT - (Circle_JoystickButton.radius * 1.5), Circle_JoystickButton.radius, YELLOW);
  }
  else { // i need a stopgap / Debounce for this
    //joystick.buttonDebounce = false;
    tft.fillCircle(Circle_JoystickButton.radius * 1.5, SCREEN_HEIGHT - (Circle_JoystickButton.radius * 1.5), Circle_JoystickButton.radius, GRAY);
  };


  // UI Score:
  tft.setTextColor(BLACK);
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
