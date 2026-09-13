#ifndef PrintWrappedTextHelper
#define PrintWrappedTextHelper
#include <Arduino.h>
#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>
#include <TouchScreen.h>

void printWrappedText(const char* text, int x, int y, int maxWidthChars, int lineHeight);

#endif