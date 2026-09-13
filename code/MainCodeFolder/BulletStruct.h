#include <stdint.h>
#ifndef BulletStruct
#define BulletStruct
#include <Arduino.h>
#include "CustShapes.h"

struct Bullet {
  bool active = true;
  byte damageStat = 1; 
  byte speed = 20;
  byte owner = 1; // 1 = Player, 2 = Enemy
  // ---- //
  SquareData squareData;
  int thickness = 2;
  // facingDirection;
};

void CreateBulletShapeData(struct Bullet *bulletGiven, int16_t centerBottom_xPos, int16_t centerBottom_yPos, int16_t height, int16_t thickness);
void MoveBullet_Step(struct Bullet *bulletGiven, float deltaTime);

#endif