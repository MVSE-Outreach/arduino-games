#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pins to control the screen 
#define CS   7
#define DC   0
#define RST  1

// Pin for the dial
#define DIAL A2

// create an instance of the library
TFT TFTscreen = TFT(CS, DC, RST);

// Use this to store the dial value
int dial = 0;
// Store the position of our bat.
int pos = 0;

void setup() {

// Put this line at the beginning of every sketch that uses the GLCD:
TFTscreen.begin();

// clear the screen with a white background
TFTscreen.background(255,255,255);
// Set the fill colour to white.
TFTscreen.fill(255,255,255);
// set the font colour to black
TFTscreen.stroke(0, 0, 0);

}

void loop() {
  
// The screen is dumb and always writes over itself.
// Blank the part of the screen that will change.
TFTscreen.fill(255,255,255);
TFTscreen.stroke(255, 255, 255);
// Draw over the rectangle.
TFTscreen.rect(1,pos,10,20);

// Read the value of the dial.
dial = analogRead(DIAL);
pos  = dial / 4;

// Set the fill colour to green.
TFTscreen.fill(0,255,0);
// set the line colour to red
TFTscreen.stroke(255, 0, 0);
// Draw the rectangle.
TFTscreen.rect(1,pos,10,20);

delay(10);

}
