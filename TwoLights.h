#ifndef TwoLights_h
#define TwoLights_h

#include "Arduino.h"
#include "Preset.h"

class TwoLights : public Preset
{
public:
  TwoLights(PixelWrapper *strip);
  void tick();

private:
  PixelWrapper *_strip;
};

#endif
