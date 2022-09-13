
#include "Arduino.h"
#include "Lesen.h"
#include "Colors.h"
#include "Util.h"

Lesen::Lesen(PixelWrapper *strip)
{
    _strip = strip;
    _strip->fill(255,255,250);
    _strip->show();
}

void Lesen::tick()
{
}
