
// These two files contain everything the arduino needs to talk to the screen.
#include <SPI.h>
#include <TFT.h>

// create the screen object we can use to draw things with
TFT screen = TFT(7, 0, 1);

void setup() {
  // initialize the screen
  screen.begin();
  // In this function we put everything that we only want to draw once.
  // For example, make the background white:
  screen.background(255,255,255);
  screen.stroke(0,0,0);
  // Add more stuff down here....
  
  // Draw a single dot on the screen
  screen.point(screen.width()/2, screen.height()/2);
  // Draw a line on the screen. (X start, Y start, X Stop, Y Stop)
  screen.line(10, 100, 100, 10);
  // Draw a rectangle on the screen (X start, Y start, X Stop, Y Stop)
  screen.rect(20, 20, 40, 60);
  // Draw a circle on the screen (X, Y, size)
  screen.circle(80, 80, 40);
  
  // Text
  // Set how big the text should be. 1 = 10 pixels, 2 = 20 pixels etc...
  screen.setTextSize(1);
  // Write some text at position (X, Y)
  screen.text("Digi-Makers Rocks!", 10, 80);
  
  delay(1000);
  // Colours
  // Set the background color. Do this first or you will cover everything up!
//  screen.background(0,0,255);
  // Set the colour of lines, and borders. Call this before line, point, circle or rect.
  screen.stroke(255, 50, 100);
  // And call this to remove the outlines and borders of the next shape you draw.
  //screen.noStroke();
  // This sets the fill colour of shapes. Call this before text, circle or rect.
  screen.fill(100, 100, 200);
  // Can you guess what this does?
  //screen.noFill();
}

void loop() {
  // In here is where we put everything we want to continuously update
  // on the screen
  
  // This code moves a circle across the screen. Can you figure out how?
  int x = -10;
  int y = 0;
  for(y=0; y<screen.width()+20; y++)
  {
    screen.circle(x, 50, 10);
    x += 1;
    delay(20);
  }
    screen.stroke(0,0,0);
   screen.text("Digi-Makers Rocks!", 50, 46);
     screen.stroke(255, 50, 100);
  // Can you make it change size as well? Can you make other shapes move?
}
