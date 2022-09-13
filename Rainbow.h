#ifndef Rainbow_h
#define Rainbow_h

#include "Arduino.h"
#include "Preset.h"

class Rainbow : public Preset
{
public:
  Rainbow(PixelWrapper *strip);
  void tick();

private:
  PixelWrapper *_strip;
};

#endif
