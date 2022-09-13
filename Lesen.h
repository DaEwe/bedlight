
#ifndef Lesen_h
#define Lesen_h

#include "Arduino.h"
#include "Preset.h"

class Lesen : public Preset
{
public:
    Lesen(PixelWrapper *strip);
    void tick();

private:
    PixelWrapper *_strip;
};

#endif
