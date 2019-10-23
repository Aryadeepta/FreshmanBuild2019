// Shen Logo Code

#include <RGBmatrixPanel.h>
#include <I2C.h>
#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.

//#define CLK A4 // USE THIS ON METRO M4 (not M0)

//#define CLK 11 // USE THIS ON ARDUINO MEGA

#define OE   9

#define LAT 10

#define A   A0

#define B   A1

#define C   A2

#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

// 32x32 matrix consumes nearly all the RAM available on the Arduino Uno --

// only a handful of free bytes remain.  So this code uses a bunch of

// precalculated data in tables to minimize RAM usage and speed things up.
static const uint16_t PROGMEM colortab[13] = {
     matrix.Color333(3,3,3),   matrix.Color333(4, 0, 0),   matrix.Color333(1,1,1), matrix.Color333(0,0,0), matrix.Color333(0,1,0), 
     matrix.Color333(7,0,0),     matrix.Color333(5,1,1),     matrix.Color333(5,1,1),   matrix.Color333(5,1,1), matrix.Color333(5,1,1), 
     matrix.Color333(5,1,1),  matrix.Color333(5,1,1), matrix.Color333(5,1,1)
     };

static const byte PROGMEM shenPattern[2][32][32] = {
  {{0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,3,4,4,4,4,3,0,0,0,3,4,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,3,4,4,4,3,4,4,3,0,3,4,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,3,4,4,3,3,3,4,4,3,0,3,4,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,3,4,4,3,3,4,4,3,0,3,4,4,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,3,4,4,4,3,3,3,3,0,3,4,4,4,3,3,3,3,3,3,3,0,0,0,3,3,3,3,0,0},
  {0,0,0,3,4,4,4,4,3,3,0,3,4,4,4,4,4,4,3,3,4,4,4,3,0,3,4,4,4,4,3,0},
  {0,0,3,3,3,3,3,4,4,3,3,4,4,4,4,4,4,4,3,4,4,3,4,3,3,4,4,4,4,4,4,3},
  {0,3,4,4,4,4,3,4,4,3,3,4,4,3,3,4,4,3,4,4,3,3,4,3,3,4,4,3,3,4,3,0},
  {0,3,4,3,3,3,3,4,4,3,4,4,4,3,4,4,3,3,4,4,4,4,3,3,4,4,3,3,4,3,3,0},
  {0,3,4,3,3,3,4,4,4,3,4,4,3,3,4,4,3,3,4,4,3,3,3,4,4,3,3,4,4,3,3,0},
  {0,3,4,4,4,4,4,4,3,4,4,3,3,4,4,3,3,3,3,4,4,3,4,4,3,3,4,4,3,3,0,0},
  {0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0},
  {0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0},
  {0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,4,4,0,0,0,0},
  {0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,4,4,4,4,4,0,0,0,0,0,0,0,4,0,0,0},
  {0,0,0,4,4,4,4,4,4,4,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,4,0,0,0},
  {0,0,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,4,0,0,0,0,4,4,0,0},
  {0,4,4,4,4,4,4,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,4,4,4,0},
  {0,4,4,4,4,4,4,4,0,0,0,4,4,0,0,0,0,4,0,0,0,0,4,4,0,0,0,0,4,4,4,0},
  {4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,4,4,0,0,0,0,4,0,0,0,0,0,4,4,4,4},
  {4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,4,4,0,0,0,0,4,4,0,0,0,0,4,4,4,4,4},
  {4,4,4,4,4,4,4,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,0,0,0,0,4,4,4,4,4},
  {4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,0,0,0,0,4,0,0,0,0,4,4,4,4,4,4},
  {0,4,4,4,4,4,4,0,0,0,0,0,4,4,0,4,4,4,0,0,0,0,0,0,0,4,4,4,4,4,4,0},
  {0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,4,4,4,4,4,4,0,0},
  {0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,4,4,4,4,4,4,0,0,0},
  {0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0},
  {0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0}},
  {{0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,3,4,4,4,4,3,0,0,0,3,4,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,3,4,4,4,3,4,4,3,0,3,4,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,3,4,4,3,3,3,4,4,3,0,3,4,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,3,4,4,3,3,4,4,3,0,3,4,4,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,3,4,4,4,3,3,3,3,0,3,4,4,4,3,3,3,3,3,3,3,0,0,0,3,3,3,3,0,0},
  {0,0,0,3,4,4,4,4,3,3,0,3,4,4,4,4,4,4,3,3,4,4,4,3,0,3,4,4,4,4,3,0},
  {0,0,3,3,3,3,3,4,4,3,3,4,4,4,4,4,4,4,3,4,4,3,4,3,3,4,4,4,4,4,4,3},
  {0,3,4,4,4,4,3,4,4,3,3,4,4,3,3,4,4,3,4,4,3,3,4,3,3,4,4,3,3,4,3,0},
  {0,3,4,3,3,3,3,4,4,3,4,4,4,3,4,4,3,3,4,4,4,4,3,3,4,4,3,3,4,3,3,0},
  {0,3,4,3,3,3,4,4,4,3,4,4,3,3,4,4,3,3,4,4,3,3,3,4,4,3,3,4,4,3,3,0},
  {0,3,4,4,4,4,4,4,3,4,4,3,3,4,4,3,3,3,3,4,4,3,4,4,3,3,4,4,3,3,0,0},
  {0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0},
  {0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0},
  {0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,4,4,0,0,0,0},
  {0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,4,4,4,4,4,0,0,0,0,0,0,0,4,0,0,0},
  {0,0,0,4,4,4,4,4,4,4,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,4,0,0,0},
  {0,0,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,4,0,0,0,0,4,4,0,0},
  {0,4,4,4,4,4,4,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,4,4,4,0},
  {0,4,4,4,4,4,4,4,0,0,0,4,4,0,0,0,0,4,0,0,0,0,4,4,0,0,0,0,4,4,4,0},
  {4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,4,4,0,0,0,0,4,0,0,0,0,0,4,4,4,4},
  {4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,4,4,0,0,0,0,4,4,0,0,0,0,4,4,4,4,4},
  {4,4,4,4,4,4,4,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,0,0,0,0,4,4,4,4,4},
  {4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,0,0,0,0,4,0,0,0,0,4,4,4,4,4,4},
  {0,4,4,4,4,4,4,0,0,0,0,0,4,4,0,4,4,4,0,0,0,0,0,0,0,4,4,4,4,4,4,0},
  {0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,4,4,4,4,4,4,0,0},
  {0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,4,4,4,4,4,4,0,0,0},
  {0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0},
  {0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0}}
};


static const byte PROGMEM kirbyPattern[2][32][32] = {
                        {{0,  3,  3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
                         {3, 12, 11, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0}, 
                         {3, 11, 11, 11, 3, 3, 11, 11, 11, 11, 12, 12, 3, 0, 0, 0, 3, 5, 5, 3, 0, 0, 0, 0}, 
                         {0,  3, 3, 10, 3, 10, 10, 10, 11, 5, 11, 12, 12, 3, 0, 3, 5, 5, 5, 3, 0, 0, 0, 0}, 
                         {0,  0, 0, 3, 3, 10, 10, 10, 10, 5, 5, 11, 12, 12, 3, 5, 5, 5, 3, 0, 0, 0, 0, 0}, 
                         {0,  0, 3, 3, 10, 3, 3, 3, 10, 10, 5, 11, 12, 12, 3, 5, 5, 3, 0, 0, 0, 0, 0, 0}, 
                         {0,  3, 10, 9, 3, 0, 0, 3, 3, 10, 10, 11, 11, 12, 3, 5, 3, 0, 0, 0, 0, 0, 0, 0}, 
                         {0,  3, 9, 9, 3, 0, 3, 3, 3, 10, 10, 3, 11, 12, 12, 3, 0, 0, 0, 0, 0, 0, 0, 0}, 
                         {3,  9, 9, 9, 8, 3, 3, 3, 9, 9, 3, 5, 3, 12, 12, 3, 0, 0, 3, 3, 3, 0, 0, 0}, 
                         {3,  9, 9, 8, 8, 8, 8, 8, 9, 9, 3, 5, 5, 3, 12, 3, 0, 3, 5, 5, 3, 0, 0, 0}, 
                         {3,  9, 8, 8, 8, 3, 3, 3, 8, 9, 3, 5, 3, 11, 12, 3, 3, 5, 5, 5, 3, 0, 0, 0}, 
                         {0, 3, 8, 8, 3, 0, 0, 3, 3, 9, 9, 3, 10, 11, 12, 3, 5, 5, 5, 3, 0, 0, 0, 0}, 
                         {0, 3, 8, 7, 3, 0, 3, 3, 3, 8, 9, 10, 10, 11, 3, 5, 5, 5, 3, 0, 0, 0, 0, 0}, 
                         {0, 0, 3, 7, 7, 3, 3, 3, 8, 8, 5, 10, 10, 11, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0}, 
                         {0, 0, 3, 7, 6, 6, 6, 7, 8, 5, 5, 10, 10, 11, 3, 0, 0, 0, 2, 4, 0, 4, 4, 4}, 
                         {0, 0, 0, 3, 6, 6, 6, 7, 8, 5, 9, 10, 10, 11, 3, 0, 0, 0, 2, 4, 0, 4, 0, 4}, 
                         {0, 0, 0, 3, 6, 6, 6, 7, 8, 8, 9, 10, 3, 3, 0, 0, 0, 2, 2, 4, 4, 4, 0, 4}, 
                         {0, 0, 0, 0, 3, 3, 7, 7, 8, 8, 3, 3, 10, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0}, 
                         {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 10, 10, 11, 3, 0, 2, 2, 0, 4, 4, 4, 4, 4}, 
                         {0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 3, 10, 11, 3, 2, 2, 0, 0, 4, 0, 0, 0, 4}, 
                         {0, 0, 0, 4, 4, 4, 4, 4, 4, 2, 2, 2, 3, 3, 2, 2, 2, 0, 0, 4, 4, 4, 4, 4}, 
                         {0, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, 
                         {0, 0, 0, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, 
  {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0}, {3, 3, 3, 0, 3, 3, 11, 11, 11, 11, 12, 12, 3, 0, 0, 0, 3, 5, 5, 3, 0, 0, 0, 0}, {11, 11, 11, 3, 3, 10, 10, 10, 11, 5, 11, 12, 12, 3, 0, 3, 5, 5, 5, 3, 0, 0, 0, 0}, {11, 11, 10, 3, 3, 10, 10, 10, 10, 5, 5, 11, 12, 12, 3, 5, 5, 5, 3, 0, 0, 0, 0, 0}, {3, 3, 3, 3, 10, 3, 3, 3, 10, 10, 5, 11, 12, 12, 3, 5, 5, 3, 0, 0, 0, 0, 0, 0}, {0, 3, 10, 9, 3, 0, 0, 3, 3, 10, 10, 11, 11, 12, 3, 5, 3, 0, 0, 0, 0, 0, 0, 0}, {0, 3, 9, 9, 3, 0, 3, 3, 3, 10, 10, 3, 11, 12, 12, 3, 0, 0, 0, 0, 0, 0, 0, 0}, {3, 9, 9, 9, 8, 3, 3, 3, 9, 9, 3, 5, 3, 12, 12, 3, 0, 0, 3, 3, 3, 0, 0, 0}, {3, 9, 9, 8, 8, 8, 8, 8, 9, 9, 3, 5, 5, 3, 12, 3, 0, 3, 5, 5, 3, 0, 0, 0}, {3, 9, 8, 8, 8, 3, 3, 3, 8, 9, 3, 5, 3, 11, 12, 3, 3, 5, 5, 5, 3, 0, 0, 0}, {0, 3, 8, 8, 3, 0, 0, 3, 3, 9, 9, 3, 10, 11, 12, 3, 5, 5, 5, 3, 0, 0, 0, 0}, {0, 3, 8, 7, 3, 0, 3, 3, 3, 8, 9, 10, 10, 11, 3, 5, 5, 5, 3, 0, 0, 0, 0, 0}, {0, 0, 3, 7, 7, 3, 3, 3, 8, 8, 5, 10, 10, 11, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0}, {0, 0, 3, 7, 6, 6, 6, 7, 8, 5, 5, 10, 10, 11, 3, 0, 0, 0, 2, 4, 0, 4, 4, 4}, {0, 0, 0, 3, 6, 6, 6, 7, 8, 5, 9, 10, 10, 11, 3, 0, 0, 0, 2, 4, 0, 4, 0, 4}, {0, 0, 0, 3, 6, 6, 6, 7, 8, 8, 9, 10, 3, 3, 0, 0, 0, 2, 2, 4, 4, 4, 0, 4}, {0, 0, 0, 0, 3, 3, 7, 7, 8, 8, 3, 3, 10, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 10, 10, 11, 3, 0, 2, 2, 0, 4, 4, 4, 4, 4}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 3, 10, 11, 3, 2, 2, 0, 0, 4, 0, 0, 0, 4}, {0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 2, 2, 3, 3, 2, 2, 2, 0, 0, 4, 4, 4, 4, 4}, {0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
};
void setup() {
  Serial.begin(9600);
  if (Serial)
    Serial.println("program started");
  I2C::initialize(0x1);
  matrix.begin();
  if(I2CgetAllianceColor()==0){matrix.fillRect(0, 0, 32, 32, matrix.Color333(4,0,0));}else{matrix.fillRect(0, 0, 32, 32, matrix.Color333(0,4,0));}

}
byte        counter= 0;
byte        mapping= 0;
short int megaCounter=1;
byte slide=1;
uint8_t red = 4;
uint8_t green = 7;
void loop() {
  counter = (counter + 1) % 10;
  if (counter == 0)
  {
    mapping = (mapping + 1) % 2;
    megaCounter = (megaCounter + 1) % 21;
  }
  if(megaCounter==0){
    megaCounter=1;
    slide = (slide + 1) % 2;
    if(I2CgetAllianceColor()==0){matrix.fillRect(0, 0, 32, 32, matrix.Color333(4,0,0));}else{matrix.fillRect(0, 0, 32, 32, matrix.Color333(0,4,0));}
  }
  switch(slide){
    case 0:
      for (uint8_t row=0; row<32; row++) 
    {
      for (uint8_t col=0; col<32; col++)
        {
          uint8_t colorindex = (int8_t)pgm_read_byte(&shenPattern[mapping][col][row]);
          uint16_t pixel = colortab[colorindex];
          matrix.drawPixel(row, col, pixel);
        }
    }
      break;
    case 1:
      for (uint8_t row=0; row<24; row++) 
    {
      for (uint8_t col=0; col<24; col++)
        {
          uint8_t colorindex = (int8_t)pgm_read_byte(&kirbyPattern[mapping][row][col]);
          uint16_t pixel = colortab[colorindex];
          matrix.drawPixel(row+4, col+4, pixel);
        }
    }
      break;
  }
}
