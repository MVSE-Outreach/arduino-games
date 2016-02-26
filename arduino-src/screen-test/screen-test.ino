#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pins to control the screen 
#define CS   7
#define DC   0
#define RST  1

// create an instance of the library
TFT TFTscreen = TFT(CS, DC, RST);

// Use this to count upwards forever.
int counter = 0;

// array of letters to print to the screen
char letters[10];

void setup() {

// Put this line at the beginning of every sketch that uses the GLCD:
TFTscreen.begin();

// clear the screen with a white background
TFTscreen.background(255,255,255);
// Set the fill colour to white.
TFTscreen.fill(255,255,255);
// set the font colour to black
TFTscreen.stroke(0, 0, 0);
// set the font size
TFTscreen.setTextSize(2);
// ste the font size very large for the loop
TFTscreen.setTextSize(2);
}

void loop() {
// Write hello world to the screen.
TFTscreen.text("Hello World!", 1, 20);

// The screen is dumb and always writes over itself.
// Blank the part of the screen that will change.

TFTscreen.rect(1,40,100,40);

// Print out the counter number.
String count = String(counter);
count.toCharArray(letters,10);
TFTscreen.text(letters, 1,40);

// wait for a moment then loop back round.
delay(500);
counter = counter + 1;
}
