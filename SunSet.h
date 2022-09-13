#ifndef SunSet_h
#define SunSet_h

#include "Arduino.h"
#include "Preset.h"

class SunSet : public Preset
{
public:
  SunSet(PixelWrapper *strip);
  void tick();
  void step();

private:
  PixelWrapper *_strip;
  byte _phase;
  int _r; 
  int _g;
  int _b;
  int _lastticktime;
  int _steptime;
};

#endif
