// plasma demo for Adafruit RGBmatrixPanel library.
// Demonstrates unbuffered animation on our 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

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
     matrix.Color333(4, 4, 4),   matrix.Color333(4, 0, 0),   matrix.Color333(1,1,1), matrix.Color333(0,0,0), matrix.Color333(0,1,0), 
     matrix.Color333(7,0,0),     matrix.Color333(5,1,1),     matrix.Color333(5,1,1),   matrix.Color333(5,1,1), matrix.Color333(5,1,1), 
     matrix.Color333(5,1,1),  matrix.Color333(5,1,1), matrix.Color333(5,1,1)
     };
//static const uint16_t PROGMEM colortab[13] = {
//     matrix.Color333(4, 4, 4),   matrix.Color333(4, 0, 0),   matrix.Color333(1,1,1), matrix.Color333(0,0,0), matrix.Color333(0,1,0), 
//     matrix.Color333(7,0,0),     matrix.Color333(7,1,1),     matrix.Color333(6,1,1),   matrix.Color333(5,1,1), matrix.Color333(5,2,2), 
//     matrix.Color333(4,2,2), matrix.Color333(4,3,3), matrix.Color333(3,2,2)
//     };
static const uint8_t PROGMEM pattern[2][32][32] = {
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
  matrix.begin();
  matrix.fillRect(0, 0, 32, 32, matrix.Color333(5,0,0));
}

long        counter= 0;
long        mapping= 0;
uint8_t red = 4;
uint8_t green = 7;

void loop() {
  counter = (counter + 1) % 10;
  if (counter == 0)
  {
    mapping = (mapping + 1) % 2;
  }
  for (uint8_t row=0; row<24; row++) 
    {
      for (uint8_t col=0; col<24; col++)
        {
          uint8_t colorindex = (int8_t)pgm_read_byte(&pattern[mapping][row][col]);
          uint16_t pixel = colortab[colorindex];
          matrix.drawPixel(row+4, col+4, pixel);
        }
    }
}
