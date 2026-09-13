#ifndef BulletStruct
#define BulletStruct
#include <Arduino.h>
#include "CustShapes.h"

struct Bullet {
  bool active = false;
  byte damageStat = 1; 
  byte speed = 20;
  LineData lineData;
  byte owner = 1; // 1 = Player, 2 = Enemy
  // facingDirection;
};

void MoveBullet_Step(struct Bullet &bulletGiven, float deltaTime);

#endif