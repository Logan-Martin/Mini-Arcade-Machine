#ifndef CustShapes
#define CustShapes
#include <Arduino.h> // Need to include this in header files if i want to use Arduino types
// tutorial I followed: https://www.youtube.com/watch?v=BdstuZP6l5E&t=33s
#include "CustomColors.h"
#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>
#include <TouchScreen.h>

struct Point {
  int16_t xPos;
  int16_t yPos;
};

struct LineData {
  Point pointA;
  Point pointB;
};

// (!?) if I do char [] list = "hello"; I don't need to declare the size of the list of chars

void SetPointB_OfLine_BasedOnLength_And_PointA(LineData &lineToChange, int16_t lengthGiven);

struct CircleData {
  int16_t xPos = 0;
  int16_t yPos = 0;
  int16_t radius = 20;
  uint16_t color = GRAY;
  bool drawDebounce = false;
};

struct TriangleData {
  int16_t x0; 
  int16_t y0; 

  int16_t x1; 
  int16_t y1; 

  int16_t x2; 
  int16_t y2;

  uint16_t color = WHITE;
};

#include "Character.h"

Point GetCenterPoint(TriangleData &triangle);

//void SetInitTrianglePts_BasedOn_LengthRelation(TriangleData &triangle, );
void Init_CenterTriangleBasedOnCenterPoint(TriangleData &triangle, Point newCenterPoint);
void UpdateTrianglePoints(TriangleData &triangle, float xChange, float yChange);
void fillTriangle_Helper_CHAR(struct CharacterStruct *charStruct, uint16_t color);

#endif
