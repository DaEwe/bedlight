#ifndef Police_h
#define Police_h

#include "Arduino.h"
#include "Preset.h"


class Police: public Preset {
  public:
    Police(PixelWrapper* strip);
    void tick();
  private:
    PixelWrapper* _strip;
    int _lastticktime;
    int _quarter;
    bool _flip; 
};




#endif
