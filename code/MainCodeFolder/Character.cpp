#include "Character.h"

void SetUpCharacter(struct CharacterStruct *charStruct, int16_t xCenterPos, int16_t yCenterPos, uint16_t color, struct TriangleData *initTriRelationship) { //struct TriangleData &initTriRelationship
  charStruct->centerPoint.xPos = xCenterPos;
  charStruct->centerPoint.yPos = yCenterPos;
  charStruct->triangleData.color = color;
  
  if (initTriRelationship == nullptr) {
    charStruct->triangleData.x0 = 0;
    charStruct->triangleData.y0 = 0;
    charStruct->triangleData.x1 = -30;
    charStruct->triangleData.y1 = -30;
    charStruct->triangleData.x2 = -60;
    charStruct->triangleData.y2 = 0;
  }
  else {
    charStruct->triangleData.x0 = initTriRelationship->x0;
    charStruct->triangleData.y0 = initTriRelationship->y0;
    charStruct->triangleData.x1 = initTriRelationship->x1;
    charStruct->triangleData.y1 = initTriRelationship->y1;
    charStruct->triangleData.x2 = initTriRelationship->x2;
    charStruct->triangleData.y2 = initTriRelationship->y2;
  }

  // ----------- //
  CustShapes::Init_CenterTriangleBasedOnCenterPoint(charStruct->triangleData, charStruct->centerPoint);
}