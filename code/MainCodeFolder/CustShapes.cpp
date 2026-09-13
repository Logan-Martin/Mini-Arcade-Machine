#include "CustShapes.h"
#include "CustomColors.h"

Point GetCenterPoint(TriangleData &triangle) {
  Point tempPoint;
  tempPoint.xPos = ((triangle.x0 + triangle.x1 + triangle.x2) / 3);
  tempPoint.yPos = ((triangle.y0 + triangle.y1 + triangle.y2) / 3);
  return tempPoint;
};

void SetPointB_OfLine_BasedOnLength_And_PointA(LineData &lineToChange, int16_t lengthGiven) {
  lineToChange.pointB.xPos = lineToChange.pointA.xPos;
  lineToChange.pointB.yPos = lineToChange.pointA.yPos;

  lineToChange.pointB.yPos += (lengthGiven);
};

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