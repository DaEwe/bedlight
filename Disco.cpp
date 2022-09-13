
#include "Arduino.h"
#include "Disco.h"
#include "Colors.h"
#include "Util.h"

Disco::Disco(PixelWrapper *strip)
{
  _strip = strip;
  _lasttick =millis();
}

void Disco::tick()
{
  int currentTime = millis();
  if (currentTime - _lasttick < 500) {
    return;
  }
  _lasttick=currentTime;
  _strip->fill(random(255),random(255),random(255));
  _strip->show();
}
