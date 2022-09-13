#include "Arduino.h"
#include "Rainbow.h"
#include "Colors.h"
#include "Util.h"

Rainbow::Rainbow(PixelWrapper *strip)
{
  _strip = strip;
}

void Rainbow::tick()
{
  _strip->setPixelColor(random(_strip->getNumRows()),random(_strip->getPixelPerRow()),random(255),random(255),random(255));
  _strip->show();
}
