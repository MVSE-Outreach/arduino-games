// These two files contain everything the arduino needs to talk to the screen.
#include <SPI.h>
#include <TFT.h>

// create an instance of the library
TFT screen = TFT(7, 0, 1);

void setup() {
  // initialize the screen
  screen.begin();
  // In this function we put everything that we only want to draw once.
  // For example, make the background white:
  screen.background(255,255,255);
  // Add more stuff down here....
}

void loop() {
  // Set the text color, in this case black.
  screen.stroke(0,0,0);
  // Set how big the text should be. 1 = 10 pixels, 2 = 20 pixels etc...
  screen.setTextSize(2);
  // Write some text at position (X, Y)
  screen.text("Hello World!", 10, 20);
  // Add more stuff down here...
}
