#include "BulletStruct.h"
#include "CustShapes.h"

void MoveBullet_Step(struct Bullet &bulletGiven, float deltaTime) {
  //for (int num = 0; num < sizeOfBulletList; ++num) {
  //  Bullet currBullet = listOfBullets[num];
  if (bulletGiven.active == true) {
    bulletGiven.lineData.pointA.yPos += (bulletGiven.speed * deltaTime);
    bulletGiven.lineData.pointB.yPos += (bulletGiven.speed * deltaTime);
  }
}
