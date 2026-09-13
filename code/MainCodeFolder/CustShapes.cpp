#include "CustShapes.h"
#include "CustomColors.h"
#include "BulletStruct.h"
extern Elegoo_TFTLCD tft; // works bc CustomShapes.h has #include for the TFT libraries like the Main ino

Point GetCenterPoint(TriangleData &triangle) {
  Point tempPoint;
  tempPoint.xPos = ((triangle.x0 + triangle.x1 + triangle.x2) / 3);
  tempPoint.yPos = ((triangle.y0 + triangle.y1 + triangle.y2) / 3);
  return tempPoint;
};

// 0000 //
void SetPointB_OfLine_BasedOnLength_And_PointA(LineData *lineToChange, int16_t lengthGiven) {
  lineToChange->pointB.xPos = lineToChange->pointA.xPos;
  lineToChange->pointB.yPos = lineToChange->pointA.yPos;

  lineToChange->pointB.yPos += (lengthGiven);
};

void CenterSquare_BasedOnThickness(SquareData *squareData) {
  int16_t offsetTemp = (squareData->points[0].xPos - squareData->points[2].xPos);
  for (int i = 0; i < 4; i++ ) { //0, 1, 2, 3
      squareData->points[i].xPos += offsetTemp;
  }
};

struct SquareData CreateSquareFromLineDataAndThickness(LineData lineData, int16_t thickness) {
  struct SquareData squareTemp;
  
  squareTemp.points[0].xPos = lineData.pointA.xPos;
  squareTemp.points[0].yPos = lineData.pointA.yPos;

  squareTemp.points[1].xPos = lineData.pointB.xPos;
  squareTemp.points[1].yPos = lineData.pointB.yPos;
  //

  squareTemp.points[2].xPos = lineData.pointA.xPos + thickness;
  squareTemp.points[2].yPos = lineData.pointA.yPos + thickness;
  
  squareTemp.points[3].xPos = lineData.pointB.xPos + thickness;
  squareTemp.points[3].yPos = lineData.pointB.yPos + thickness;

  CenterSquare_BasedOnThickness(&squareTemp);
  return squareTemp;
};
// ---- //

void Init_CenterTriangleBasedOnCenterPoint(TriangleData &triangle, Point newCenterPoint) {
  // Want to get relation of each point to its own overall triangle centerpoint
  // from there then we can "re-position" the triangle to a position, then remake the triangle based on its center to points relationships
  // like distance, but for both X and Y

  Point triangleSelfCenterPoint = GetCenterPoint(triangle);
  // 00000 //

  Point distBetween_P1_And_Triangle_CenterPoint;
  distBetween_P1_And_Triangle_CenterPoint.xPos = (triangle.x0 - triangleSelfCenterPoint.xPos);
  distBetween_P1_And_Triangle_CenterPoint.yPos = (triangle.y0 - triangleSelfCenterPoint.yPos);

  Point distBetween_P2__And_Triangle_CenterPoint;
  distBetween_P2__And_Triangle_CenterPoint.xPos = (triangle.x1 - triangleSelfCenterPoint.xPos);
  distBetween_P2__And_Triangle_CenterPoint.yPos = (triangle.y1 - triangleSelfCenterPoint.yPos);

  Point distBetween_P3__And_Triangle_CenterPoint;
  distBetween_P3__And_Triangle_CenterPoint.xPos = (triangle.x2 - triangleSelfCenterPoint.xPos);
  distBetween_P3__And_Triangle_CenterPoint.yPos = (triangle.y2 - triangleSelfCenterPoint.yPos);

  // Now actually "re-position" that triangle w/ the relationships:
  triangle.x0 = (newCenterPoint.xPos + distBetween_P1_And_Triangle_CenterPoint.xPos);
  triangle.y0 = (newCenterPoint.yPos + distBetween_P1_And_Triangle_CenterPoint.yPos);

  triangle.x1 = (newCenterPoint.xPos + distBetween_P2__And_Triangle_CenterPoint.xPos);
  triangle.y1 = (newCenterPoint.yPos + distBetween_P2__And_Triangle_CenterPoint.yPos);

  triangle.x2 = (newCenterPoint.xPos + distBetween_P3__And_Triangle_CenterPoint.xPos);
  triangle.y2 = (newCenterPoint.yPos + distBetween_P3__And_Triangle_CenterPoint.yPos);
};

void UpdateTrianglePoints(TriangleData &triangle, float xChange, float yChange) {
  triangle.x0 += xChange;
  triangle.y0 += yChange;

  triangle.x1 += xChange;
  triangle.y1 += yChange;

  triangle.x2 += xChange;
  triangle.y2 += yChange;
};

void fillTriangle_Helper_CHAR(struct CharacterStruct *charStruct, uint16_t color) {
  if (color == NULL) {
    tft.fillTriangle(charStruct->triangleData.x0, charStruct->triangleData.y0, charStruct->triangleData.x1, charStruct->triangleData.y1, charStruct->triangleData.x2, charStruct->triangleData.y2, charStruct->triangleData.color);
  }
  else {
    tft.fillTriangle(charStruct->triangleData.x0, charStruct->triangleData.y0, charStruct->triangleData.x1, charStruct->triangleData.y1, charStruct->triangleData.x2, charStruct->triangleData.y2, color);
  }
}

void fillTriHelper_CHAR_MultiInOneCall(struct CharacterStruct *charStruct, uint16_t color) {
  fillTriangle_Helper_CHAR(charStruct, color);
  fillTriangle_Helper_CHAR(charStruct, color);
  fillTriangle_Helper_CHAR(charStruct, color);
  fillTriangle_Helper_CHAR(charStruct, color);
  fillTriangle_Helper_CHAR(charStruct, color);
  fillTriangle_Helper_CHAR(charStruct, color);
}

void fillSquare_Helper_Bullet(struct Bullet *bulletGiven, uint16_t color) {
  SquareData tempSquareData = bulletGiven->squareData;
  tft.drawRect(tempSquareData.points[0].xPos, tempSquareData.points[0].yPos, tempSquareData.width, tempSquareData.height, color);
}
