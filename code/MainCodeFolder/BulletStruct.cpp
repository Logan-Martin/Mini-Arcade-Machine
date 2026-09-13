#include "BulletStruct.h"
#include "CustShapes.h"

void MoveBullet_Step(struct Bullet *bulletGiven, float deltaTime) {
  if (bulletGiven->active == true) {
    for (int i = 0; i < 4; i++ ) { //0, 1, 2, 3
      //bulletGiven.squareData.points[i].xPos += (bulletGiven.speed * deltaTime);
      bulletGiven->squareData.points[i].yPos += (bulletGiven->speed * deltaTime);
    }
  }
}

void CreateBulletShapeData(struct Bullet *bulletGiven, int16_t centerBottom_xPos, int16_t centerBottom_yPos, int16_t height, int16_t thickness) {
  bulletGiven->squareData.height = height; // for tft.drawRect eventually
  bulletGiven->squareData.width = thickness;
  // ---- //
  Point tempPointData;
  tempPointData.xPos = centerBottom_xPos;
  tempPointData.yPos = centerBottom_yPos;

  LineData tempLineData;
  tempLineData.pointA = tempPointData;

  SetPointB_OfLine_BasedOnLength_And_PointA(&tempLineData, height); // Point -> Line
  bulletGiven->squareData = CreateSquareFromLineDataAndThickness(tempLineData, thickness); // Line -> Square [Auto re-centers shape]
}