#include "CustShapes.h"
#include "CustomColors.h"

Point GetCenterPoint(TriangleData triangle) {
  Point tempPoint;
  tempPoint.xPos = ((triangle.x0 + triangle.x1 + triangle.x2) / 3);
  tempPoint.yPos = ((triangle.y0 + triangle.y1 + triangle.y2) / 3);
  return tempPoint;
};

void UpdateTrianglePoints(TriangleData triangle, CharacterStruct plr) {
  triangle.x0 = (plr. );
  triangle.y0 = ();

  triangle.x1 = ();
  triangle.y1 = ();

  triangle.x2 = ();
  triangle.y2 = ();
};