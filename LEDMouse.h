
#ifndef LEDMouse_h
#define LEDMouse_h

#include "Arduino.h"
#include "Preset.h"

class LEDMouse : public Preset
{
public:
    LEDMouse(PixelWrapper *strip);
    void tick();

private:
    PixelWrapper *_strip;
    int _lasttick;
    int _lastchange;
    int _pos_row;
    int _pos_pix;
    boolean _direction;
    
};

#endif
