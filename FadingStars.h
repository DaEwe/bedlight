#ifndef FadingStars_h
#define FadingStars_h

#include "Arduino.h"
#include "Preset.h"

class FadingStars : public Preset
{
public:
  FadingStars(PixelWrapper *strip);
  ~FadingStars();
  void tick();

private:
  void addStar();
  PixelWrapper *_strip;
  int *_starstates;
  int *_idxs;
  int _numPixels;
  int _maxNumStars;
  int _numShining;
  int _freeIdx;
  int _lastBornMillis;
  int _tickidx;
};

#endif
