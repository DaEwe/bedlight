#ifndef Disco_h
#define Disco_h

#include "Arduino.h"
#include "Preset.h"

class Disco : public Preset
{
public:
    Disco(PixelWrapper *strip);
    void tick();

private:
    PixelWrapper *_strip;
    int _lasttick;
};

#endif
