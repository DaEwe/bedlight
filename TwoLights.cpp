#include "Arduino.h"
#include "TwoLights.h"
#include "Colors.h"
#include "Util.h"

TwoLights::TwoLights(PixelWrapper *strip)
{
  int parts = strip->getPixelPerRow() / 5;
  _strip = strip;
  _strip->setArea(1, parts, _strip->getNumRows() - 3, parts, 255, 255, 255);
  _strip->setArea(1, parts *3+1, _strip->getNumRows() - 3, parts, 255, 255, 255);
  _strip->show();
}

void TwoLights::tick()
{
}
