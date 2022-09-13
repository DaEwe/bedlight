#include "Arduino.h"
#include "FadingStars.h"
#define PERCENTSHINE 60
#define WAITBETWEENSTARS 100
FadingStars::FadingStars(PixelWrapper* strip) {
  _strip = strip;
  _numPixels = strip->numPixels();
  _maxNumStars = (int)_numPixels / 100 * PERCENTSHINE;
  _starstates = new int[_maxNumStars];
  _lastBornMillis = millis();
  _numShining = 0;
  _idxs = new int[_maxNumStars];
  _freeIdx = 0;
  _tickidx = 0;
  for (int i = 0; i < _maxNumStars; i++) {
    _starstates[i] = 0;
  }
  randomSeed(analogRead(0));
}

void FadingStars::addStar() {
  int currentTime = millis();
  if (currentTime - _lastBornMillis < WAITBETWEENSTARS) {
    return;
  }
  int randnum = random(_maxNumStars);
  if (randnum < (_maxNumStars - _numShining)) {
    _lastBornMillis = currentTime;
    _numShining++;
    int starIdx = random(_numPixels);
    _starstates[_freeIdx] = 1;
    _idxs[_freeIdx] = starIdx;
    _freeIdx = (_freeIdx + 1) % _maxNumStars;
  }
}




void FadingStars::tick() {
  _tickidx = (_tickidx + 1) % 10;
  if (_tickidx != 0) {
    return;
  }
  _strip->clear();
  this->addStar();
  for (int i = 0; i < _maxNumStars; i++) {
    if (_starstates[i] != 0) {
      if (_starstates[i] == 255) {
        //goes dark now
        _starstates[i] = 254;
      }
      if (_starstates[i] == 2) {
        //dies now
        _numShining--;
      }
      if (_starstates[i] % 2 == 0) {
        _starstates[i] -= 2;
      } else {
        _starstates[i] += 2;
      }
      _strip->setPixelColor(_idxs[i], _starstates[i], _starstates[i], _starstates[i]);
    }
  }
  _strip->show();
}



FadingStars::~FadingStars() {
  delete[] _starstates;
  delete[] _idxs;
}
