// These two files contain everything the arduino needs to talk to the screen.
#include <SPI.h>
#include <TFT.h>

// These are the pins each of the knobs connect to
#define Horizontal_Input A5
#define Vertical_Input A0

// create an instance of the screen
TFT screen = TFT(7, 0, 1);

// How big the paddels will be:
int bat_size = 20;
// here is where we will store the position of the players
int p1_pos = 0;
int p2_pos = 0;
// Store their previous positions too. You'll see why in a second...
int old_p1_pos = 0;
int old_p2_pos = 0;
// Store the position of the ball
int ball_x = screen.height()/4;
int ball_y = screen.width()/2;
int old_ball_x = screen.height()/2;
int old_ball_y = screen.width()/2;

int ball_speed_x = 1;
int ball_speed_y = 1;


void setup() {
  screen.begin();
  screen.background(255,255,255);
  screen.setTextSize(2);
}

void loop() {
  // First, lets update and draw where the player paddles are
  // Can you remember what these lines did from the last example?
  p1_pos = analogRead(Horizontal_Input);
  p2_pos = analogRead(Vertical_Input);
  // Why do we subtract 20 from the screen height?
  p1_pos = map(p1_pos, 0, 1023, 0, screen.height()-20);
  p2_pos = map(p2_pos, 0, 1023, 0, screen.height()-20);
  
  // Now lets draw the paddles.
  if(p1_pos != old_p1_pos || p2_pos != old_p2_pos)
  {
    screen.fill(255,255,255);    
    screen.rect(3, old_p1_pos, 3, bat_size); // Player 1
    screen.rect(154, old_p2_pos, 3, bat_size); // Player 1
  }
  
  // Draw the player paddles
  screen.fill(255,0,0); // Player 1 paddle colour.
  screen.rect(3, p1_pos, 3, bat_size); // Player 1
  screen.fill(0,255,0); // Player 2 paddle colour.
  screen.rect(154, p2_pos, 3, bat_size); // Player 2
  
  // Draw the ball!
  screen.fill(255,255,255);    
  screen.circle(old_ball_x,old_ball_y,3); // erase the old ball
  screen.fill(0,0,255);    
  screen.circle(ball_x,ball_y,3); // draw the new one!
  
  // Now we need to deal with moving the ball and making sure that is
  // bounces off the edges properly!
  if(ball_y > screen.height() || ball_y < 0) 
  { 
    ball_speed_y = -ball_speed_y;
  }
  
  // check if the ball has gone off the end of the screen
  if(ball_x > screen.width()) 
  { 
    screen.stroke(0,0,0);
    screen.text(" Player\n  One\n  Wins!",10,30);
    delay(10000);
  }
  else if (ball_x < 0) 
  { 
    screen.stroke(0,0,0);
    screen.text(" Player\n  Two\n  Wins!",10,30);
    delay(10000);
  }
  else
  {
    // Has it hit player one's bat?
    if(ball_x < 4 && ball_y < p1_pos + bat_size && ball_y > p1_pos)
    {
        ball_speed_x = -ball_speed_x;
    }
    // Has it hit player two's bat?
    else if(ball_x > screen.width()-6 && ball_y < p2_pos + bat_size && ball_y > p2_pos)
    {
        ball_speed_x = -ball_speed_x;
    }
  }
  
  // Update the old positions
  old_p1_pos = p1_pos;
  old_p2_pos = p2_pos;
  old_ball_x = ball_x;
  old_ball_y = ball_y;
  ball_x = ball_x + ball_speed_x;
  ball_y = ball_y + ball_speed_y;
  
  delay(10);
}
