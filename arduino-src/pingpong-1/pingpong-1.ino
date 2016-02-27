#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pins to control the screen 
#define CS   7
#define DC   0
#define RST  1

// Pins for the player paddle positions
#define PIN_P1_BAT A2
#define PIN_P2_BAT A3

// create an instance of the library
TFT screen = TFT(CS, DC, RST);

// Player Scores
int score_p1;
int score_p2;
int position_p1;
int position_p2;

void drawPlayerScores()
{
    // This function will draw a very simple "X - Y" string where
    // X and Y are the scores for each player.

    // Set the text color to black.
    screen.stroke(0,0,0);

    // We will print five letters, so make our array five long.
    char toPrint[5];
    String S = "";
    S += String(score_p1);  // Add the player 1 score
    S += " - ";             // Separate the two scores
    // ......               // Add the player 2 score
    S.toCharArray(toPrint,5); // Convert the string to something we can show.
    // ......               // Display the text!
}

void getPlayerPositions(){
    // Read player 1 position
    // What do you think the map function does?
    position_p1 = map(analogRead(PIN_P1_BAT),0,1023-bat_h,0,screen_h);
    
    // Read player 2 position
    // ....
}

void setup() {

    // Set up the screen.
    screen.begin();
    screen.background(255,255,255);
    screen.fill(255,255,255);
    screen.stroke(0, 0, 0);
    screen.setTextSize(1);

    // Set up the player scores and bat positions.
    score_p1    = 0;
    score_p2    = 0;
    position_p1 = 0;
    position_p2 = 0;
}

void loop() {

    // Read the player positions.
    getPlayerPositions();

    // Draw the player scores.
    drawPlayerScores();

    delay(500);
}

