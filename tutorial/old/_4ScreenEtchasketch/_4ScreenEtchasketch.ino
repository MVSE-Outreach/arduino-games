// These two files contain everything the arduino needs to talk to the screen.
#include <SPI.h>
#include <TFT.h>

// These are the pins each of the knobs connect to
#define Horizontal_Input A5
#define Vertical_Input A0

// create an instance of the screen
TFT screen = TFT(7, 0, 1);

// here is where we will store the position of the cursor
int h_pos = 0;
int v_pos = 0;

void setup() {
  screen.begin();
  screen.background(255,255,255);
}

void loop() {
  // First, lets update where we think the cursor is
  h_pos = analogRead(Horizontal_Input);
  v_pos = analogRead(Vertical_Input);
  // What do you think these lines do? Have a look below
  // the code to find out.
  h_pos = map(h_pos, 0, 1023, 0, screen.width());
  v_pos = map(v_pos, 0, 1023, 0, screen.height());
  // Now lets draw the dot where the cursor is:
  // first set the color:
  screen.stroke(255,0,0);
  // Now draw the point:
  screen.point(h_pos,v_pos);
}
