#ifndef CustShapes
#define CustShapes
#include <Arduino.h> // Need to include this in header files if i want to use Arduino types
// tutorial I followed: https://www.youtube.com/watch?v=BdstuZP6l5E&t=33s
#include "CustomColors.h"

struct Point {
  int16_t xPos;
  int16_t yPos;
};

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

Point GetCenterPoint(TriangleData triangle);
void UpdateTrianglePoints(TriangleData triangle, Player plr);

#endif