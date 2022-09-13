#include "PixelWrapper.h"


PixelWrapper::PixelWrapper(int numPixTotal, int pin,  int numRows, int active) {
  _strip = new Adafruit_NeoPixel(numPixTotal, pin);
  _numRows = numRows;
  _rowDist = 100/numRows;
  _pixelPerRow = floor((numPixTotal / numRows) / active);
  _pixelDist = 0.33 * active;
  _active = active;
}

void PixelWrapper::fill(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < _numRows; i++) {
    for (int j = 0; j < _pixelPerRow; j++) {
      this->setPixelColor(i, j, r, g, b);
    }
  }
}

void PixelWrapper::drawCircle(uint16_t row, uint16_t n, uint16_t radius, uint8_t r, uint8_t g, uint8_t b){
  uint16_t min_row = max((int)(row -radius/_rowDist),0);
  uint16_t min_n = max( (int)(n-radius/_pixelDist),0);
  uint16_t max_row = min((int)(row+radius/_rowDist), _numRows);
  uint16_t max_n = min((int)(n+radius/_pixelDist), _pixelPerRow);
  for (uint16_t row_idx = min_row; row_idx < max_row; row_idx++){
    for (uint16_t n_idx = min_n; n_idx < max_n; n_idx++){
      float d_row = (row_idx - row)*_rowDist;
      float d_n = (n_idx - n) * _pixelDist;
      float dist_squared = d_row * d_row + d_n * d_n;
      if (dist_squared <= radius * radius){
        this->setPixelColor(d_row,d_n,r,g,b);
      }
    } 
  }
}


void PixelWrapper::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  _strip->setPixelColor(n * _active, r, g, b);
}

void PixelWrapper::setPixelColor(uint16_t row, uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  if (row%2==0){
  _strip->setPixelColor(row * _pixelPerRow * _active + n * _active, r, g, b);
  } else {
    _strip->setPixelColor((row+1) * _pixelPerRow * _active -1 - n * _active, r, g, b);
  }
}


void PixelWrapper::setArea(int rowStart, int pixNumStart, int rowEnd, int pixNumEnd, uint8_t r, uint8_t g, uint8_t b) {
  for (int i = rowStart; i <= rowEnd; i++) {
    for (int j = pixNumStart; j <= pixNumEnd; j++) {
      this->setPixelColor(i, j, r, g, b);
    }
  }
}

void PixelWrapper::show() {
  _strip->show();
}

int PixelWrapper::getNumRows() {
  return _numRows;
}


int PixelWrapper::getPixelPerRow() {
  return _pixelPerRow;
}


int PixelWrapper::numPixels() {
  return _numRows*_pixelPerRow;
}

void PixelWrapper::clear() {
  _strip->clear();
}

void PixelWrapper::begin() {
  _strip->begin();
}
