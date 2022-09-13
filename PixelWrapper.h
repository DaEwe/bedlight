#ifndef PixelWrapper_h
#define PixelWrapper_h
#include <Adafruit_NeoPixel.h>

class PixelWrapper {
  public:
    PixelWrapper(int numPixTotal, int pin,  int numRows, int active);
    void fill(uint8_t r, uint8_t g, uint8_t b);
    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);

    void setPixelColor(uint16_t row, uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    
    void setArea(int rowStart, int pixNumStart, int rowEnd, int pixNumEnd, uint8_t r, uint8_t g, uint8_t b);
    void drawCircle(uint16_t row, uint16_t n, uint16_t radius, uint8_t r, uint8_t g, uint8_t b);
    void show();
    int getNumRows();
    int getPixelPerRow();
    int numPixels();
    void clear();
    static uint32_t   Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
      return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
    }
    static uint32_t   Color(uint8_t r, uint8_t g, uint8_t b) {
      return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
    }
    void begin();

  private:
    Adafruit_NeoPixel* _strip;
    int _numRows;
    int _pixelPerRow;
    int _active;
    float _pixelDist;
    float _rowDist;
};
#endif
