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
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
void setup() {
  // put your setup code here, to run once:
  int frame1[24][24] = {{0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {3, 12, 11, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0}, {3, 11, 11, 11, 3, 3, 11, 11, 11, 11, 12, 12, 3, 0, 0, 0, 3, 5, 5, 3, 0, 0, 0, 0}, {0, 3, 3, 10, 3, 10, 10, 10, 11, 5, 11, 12, 12, 3, 0, 3, 5, 5, 5, 3, 0, 0, 0, 0}, {0, 0, 0, 3, 3, 10, 10, 10, 10, 5, 5, 11, 12, 12, 3, 5, 5, 5, 3, 0, 0, 0, 0, 0}, {0, 0, 3, 3, 10, 3, 3, 3, 10, 10, 5, 11, 12, 12, 3, 5, 5, 3, 0, 0, 0, 0, 0, 0}, {0, 3, 10, 9, 3, 0, 0, 3, 3, 10, 10, 11, 11, 12, 3, 5, 3, 0, 0, 0, 0, 0, 0, 0}, {0, 3, 9, 9, 3, 0, 3, 3, 3, 10, 10, 3, 11, 12, 12, 3, 0, 0, 0, 0, 0, 0, 0, 0}, {3, 9, 9, 9, 8, 3, 3, 3, 9, 9, 3, 5, 3, 12, 12, 3, 0, 0, 3, 3, 3, 0, 0, 0}, {3, 9, 9, 8, 8, 8, 8, 8, 9, 9, 3, 5, 5, 3, 12, 3, 0, 3, 5, 5, 3, 0, 0, 0}, {3, 9, 8, 8, 8, 3, 3, 3, 8, 9, 3, 5, 3, 11, 12, 3, 3, 5, 5, 5, 3, 0, 0, 0}, {0, 3, 8, 8, 3, 0, 0, 3, 3, 9, 9, 3, 10, 11, 12, 3, 5, 5, 5, 3, 0, 0, 0, 0}, {0, 3, 8, 7, 3, 0, 3, 3, 3, 8, 9, 10, 10, 11, 3, 5, 5, 5, 3, 0, 0, 0, 0, 0}, {0, 0, 3, 7, 7, 3, 3, 3, 8, 8, 5, 10, 10, 11, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0}, {0, 0, 3, 7, 6, 6, 6, 7, 8, 5, 5, 10, 10, 11, 3, 0, 0, 0, 2, 4, 0, 4, 4, 4}, {0, 0, 0, 3, 6, 6, 6, 7, 8, 5, 9, 10, 10, 11, 3, 0, 0, 0, 2, 4, 0, 4, 0, 4}, {0, 0, 0, 3, 6, 6, 6, 7, 8, 8, 9, 10, 3, 3, 0, 0, 0, 2, 2, 4, 4, 4, 0, 4}, {0, 0, 0, 0, 3, 3, 7, 7, 8, 8, 3, 3, 10, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 10, 10, 11, 3, 0, 2, 2, 0, 4, 4, 4, 4, 4}, {0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 3, 10, 11, 3, 2, 2, 0, 0, 4, 0, 0, 0, 4}, {0, 0, 0, 4, 4, 4, 4, 4, 4, 2, 2, 2, 3, 3, 2, 2, 2, 0, 0, 4, 4, 4, 4, 4}, {0, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  int frame2[24][24] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0}, {3, 3, 3, 0, 3, 3, 11, 11, 11, 11, 12, 12, 3, 0, 0, 0, 3, 5, 5, 3, 0, 0, 0, 0}, {11, 11, 11, 3, 3, 10, 10, 10, 11, 5, 11, 12, 12, 3, 0, 3, 5, 5, 5, 3, 0, 0, 0, 0}, {11, 11, 10, 3, 3, 10, 10, 10, 10, 5, 5, 11, 12, 12, 3, 5, 5, 5, 3, 0, 0, 0, 0, 0}, {3, 3, 3, 3, 10, 3, 3, 3, 10, 10, 5, 11, 12, 12, 3, 5, 5, 3, 0, 0, 0, 0, 0, 0}, {0, 3, 10, 9, 3, 0, 0, 3, 3, 10, 10, 11, 11, 12, 3, 5, 3, 0, 0, 0, 0, 0, 0, 0}, {0, 3, 9, 9, 3, 0, 3, 3, 3, 10, 10, 3, 11, 12, 12, 3, 0, 0, 0, 0, 0, 0, 0, 0}, {3, 9, 9, 9, 8, 3, 3, 3, 9, 9, 3, 5, 3, 12, 12, 3, 0, 0, 3, 3, 3, 0, 0, 0}, {3, 9, 9, 8, 8, 8, 8, 8, 9, 9, 3, 5, 5, 3, 12, 3, 0, 3, 5, 5, 3, 0, 0, 0}, {3, 9, 8, 8, 8, 3, 3, 3, 8, 9, 3, 5, 3, 11, 12, 3, 3, 5, 5, 5, 3, 0, 0, 0}, {0, 3, 8, 8, 3, 0, 0, 3, 3, 9, 9, 3, 10, 11, 12, 3, 5, 5, 5, 3, 0, 0, 0, 0}, {0, 3, 8, 7, 3, 0, 3, 3, 3, 8, 9, 10, 10, 11, 3, 5, 5, 5, 3, 0, 0, 0, 0, 0}, {0, 0, 3, 7, 7, 3, 3, 3, 8, 8, 5, 10, 10, 11, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0}, {0, 0, 3, 7, 6, 6, 6, 7, 8, 5, 5, 10, 10, 11, 3, 0, 0, 0, 2, 4, 0, 4, 4, 4}, {0, 0, 0, 3, 6, 6, 6, 7, 8, 5, 9, 10, 10, 11, 3, 0, 0, 0, 2, 4, 0, 4, 0, 4}, {0, 0, 0, 3, 6, 6, 6, 7, 8, 8, 9, 10, 3, 3, 0, 0, 0, 2, 2, 4, 4, 4, 0, 4}, {0, 0, 0, 0, 3, 3, 7, 7, 8, 8, 3, 3, 10, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 10, 10, 11, 3, 0, 2, 2, 0, 4, 4, 4, 4, 4}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 3, 10, 11, 3, 2, 2, 0, 0, 4, 0, 0, 0, 4}, {0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 2, 2, 3, 3, 2, 2, 2, 0, 0, 4, 4, 4, 4, 4}, {0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  matrix.begin();
  int      x, y, hue;
  int dist = 0;
  float    dx, dy, d;
  uint8_t  sat, val;
  uint16_t c;
  matrix.fillScreen(matrix.Color333(7, 7, 7));
  byte colorRed[13] = {matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,58.8,true),matrix.ColorHSV(0,0,0,true),matrix.ColorHSV(120,1,58.8,true),matrix.ColorHSV(0,1,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true)};
  byte colorBlue[13] = {matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,58.8,true),matrix.ColorHSV(0,0,0,true),matrix.ColorHSV(120,1,58.8,true),matrix.ColorHSV(0,1,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true),matrix.ColorHSV(0,0,100,true)};  
  for(int i=0;i<7;i++){
    colorRed[i+6]=matrix.ColorHSV(10*i,1-i/12,100-i*7.5);  
    colorBlue[i+6]=matrix.ColorHSV(10*i+240,1-i/12,100-i*7.5);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  frameDisplay(frame1,colorRed);
  delay(100)
  if(dist>8){
    dist = 0;
  } else {
    drawBall(dist);
    dist++;  
  }
  frameDisplay(frame2,colorRed);
  delay(100)
  if(dist>8){
    dist = 0;
  } else {
    drawBall(dist);
    dist++;  
  }
}
void frameDisplay(int frame[24][24], byte colors[13]){
  for(int i = 0; i<24;i++){
    for(int j=0;j<24;j++){
      int x = i+4;
      int y = j+4;
      matrix.drawPixel(x,y,colors[frame[x][y]]);
    }  
  }  
}
void drawBall(int p){
  matrix.fillRect(p+4,16,p+5,17,matrix.ColorHSV(39,1,100));  
}
