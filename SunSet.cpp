#include "Arduino.h"
#include "SunSet.h"

SunSet::SunSet(PixelWrapper* strip) {
  _strip = strip;
  _lastticktime = millis();
  _phase = 0;
  _r = 255;
  _g = 255;
  _b = 255;
  _steptime=100;
}

void SunSet::tick(){
  int currentTime = millis();
  if (currentTime - _lastticktime < _steptime) {
    return;
  }
  _lastticktime=currentTime;
  this->step();
  _strip->show();
}

void SunSet::step(){
  switch(_phase){
    case 0:
      _b--;
      if (_b==0){
        _phase=1;
      }
      break;
    case 1:
      _g--;
      if (_g==0){
        _phase=2;
      }
      break;
    case 2:
      _r--;
      if (_r==10){
        _phase=3;
        _steptime=1000;
      }
      break;
    case 3:
      _b++;
      if (_b==10){
        _phase=4;
      }
      break;
    case 4:
      _r--;
      if (_r==0){
        _steptime = 20000;
        _phase=5;
      }
      break;
    case 5:
      _b--;  
      if (_b==0){
        _steptime = 10000;
        _r = 0;
        _g = 0;
        _b = 0;
        _phase=6;
      }
      break;
    case 6:
      
    
      return;
  }
  _strip->fill(max(_r,0),max(_g,0),max(_b,0));
}
