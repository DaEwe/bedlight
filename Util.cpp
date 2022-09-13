#include "Util.h"

extern void paintArea(Adafruit_NeoPixel* strip, int min_idx, int max_idx, const int* colors) {
  for (int i = min_idx; i <= max_idx; i++) {
    strip->setPixelColor(i, strip->Color(colors[0], colors[1], colors[2]));
  }
}
