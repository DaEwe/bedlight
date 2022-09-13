#include "Arduino.h"
#include "Police.h"
#include "Colors.h"
#include "Util.h"

Police::Police(PixelWrapper* strip) {
  _strip = strip;
  _lastticktime = millis();
  _flip = false;
  _quarter = floor(strip->getPixelPerRow() / 4);
}

void Police::tick() {
  int currenttime = millis();
  if (currenttime - _lastticktime > 1000) {
    _lastticktime = currenttime;
    _flip = !_flip;

  }


  if (_flip) {
    _strip->setArea(0, 0, _strip->getNumRows() - 1, _quarter, 255, 0, 0);
    _strip->setArea(0, _quarter + 1, _strip->getNumRows() - 1, _quarter * 2, 0, 0, 255);
    _strip->setArea(0, _quarter * 2 + 1, _strip->getNumRows() - 1, _quarter * 3, 255, 0, 0);
    _strip->setArea(0, _quarter * 3 + 1, _strip->getNumRows() - 1, _strip->getPixelPerRow() - 1, 0, 0, 255);
    _strip->show();
  } else {
    _strip->setArea(0, 0, _strip->getNumRows() - 1, _quarter, 0, 0, 255);
    _strip->setArea(0, _quarter + 1, _strip->getNumRows() - 1, _quarter * 2, 255, 0, 0);
    _strip->setArea(0, _quarter * 2 + 1, _strip->getNumRows() - 1, _quarter * 3, 0, 0, 255);
    _strip->setArea(0, _quarter * 3 + 1, _strip->getNumRows() - 1, _strip->getPixelPerRow() - 1, 255, 0, 0);
    _strip->show();
  }
}
