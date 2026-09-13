#ifndef Character
#define Character
#include <Arduino.h>
#include "CustShapes.h"

struct CharacterStruct {
  // Shape Info:
  struct Point centerPoint;
  struct TriangleData triangleData;
  //byte shapeOfSprite = 1; // 0 = Circle, 1 = Triangle, 2 = Square
  
  // Other:
  byte health = 4;  // 1 to 255
  byte walkSpeed = 75; // 1 to 255
  byte attackStat = 1;

  byte type = 1; // could add a type based on numbers. like 1 = player, 2 = enemy
  int score = 0;
};

void SetUpCharacter(struct CharacterStruct *charStruct, int16_t xCenterPos, int16_t yCenterPos, uint16_t color, struct TriangleData *initTriRelationship);



#endif