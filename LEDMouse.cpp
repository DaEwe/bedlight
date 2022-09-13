
#include "Arduino.h"
#include "LEDMouse.h"
#include "Colors.h"
#include "Util.h"

LEDMouse::LEDMouse(PixelWrapper *strip)
{
  _strip = strip;
  _lasttick = millis();
  _lastchange = millis();
  _direction = true;
  _pos_pix = random(_strip->getPixelPerRow());
  _pos_row = random(_strip->getNumRows());
}

void LEDMouse::tick()
{
  int currentTime = millis();
  if (currentTime - _lasttick < 50) {
    return;
  }
  _lasttick = currentTime;
  int dec = random(10);
  if (dec > 2) {
    _pos_pix += _direction ? 1 : -1;
    if (_pos_pix == 0 || _pos_pix == _strip->getPixelPerRow()) {
      _direction = !_direction;
    }
  } else {
    if (dec==0 && _pos_row != 0){
      _pos_row--;
    } else {
      if (dec==1 &&_pos_row != _strip->getNumRows()-1){
        _pos_row++;
      } else {
        _direction = !_direction;
        }
    }
  }

  _strip->clear();
  _strip->setPixelColor(_pos_row, _pos_pix, 255, 255, 255);
  _strip->show();
}
