#include "PrintWrappedTextHelper.h"
extern Elegoo_TFTLCD tft; // works bc CustomShapes.h has #include for the TFT libraries like the Main ino

// --- Text wrapping ---
void printWrappedText(const char* text, int x, int y, int maxWidthChars, int lineHeight) {
  tft.setCursor(x, y);
  char tempText[256];
  strcpy(tempText, text);
  char* rest = tempText;
  char* word;
  String line = "";

  while ((word = strtok_r(rest, " ", &rest))) {
    if (line.length() + strlen(word) + (line.length() > 0 ? 1 : 0) > maxWidthChars) {
      tft.print(line);
      y += lineHeight;
      tft.setCursor(x, y);
      line = word;
      line += " ";
    } else {
      line += word;
      line += " ";
    }
  }
  if (line.length() > 0) {
    tft.print(line);
  }
}

