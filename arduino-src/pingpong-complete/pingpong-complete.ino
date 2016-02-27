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

const int bat_w = 5;
const int bat_h = 20;

const int ball_speed = 1;
const int ball_size  = 3;

int screen_w = 320;
int screen_h = 240;

// Player Scores
int score_p1;
int score_p2;
int position_p1;
int position_p2;

int ball_pos_x;
int ball_pos_y;
int ball_dir_x;
int ball_dir_y;

void startCountdown()
{
    int countdown = 4;
    // Make the text size nice and big.
    screen.setTextSize(3);

    while(countdown > 0){
        countdown = countdown - 1;
        
        // Make a string to show the score.
        char toPrint[2];
        String(countdown).toCharArray(toPrint,2);

        screen.stroke(0, 0, 0);
        screen.text(toPrint,screen_w/2,screen_h/2);
        
        delay(1000);    // Wait for one thousand milliseconds / one second.

        // Rub out the old text.
        screen.stroke(255,255,255);
        screen.fill(255,255,255);
        screen.rect(screen_w/2,screen_h/2,30,30);
    }
    // Put the text size back to normal.
    screen.setTextSize(1);
}

void setup() {

    // Set up the screen.
    screen.begin();
    screen.background(255,255,255);
    screen.fill(255,255,255);
    screen.stroke(0, 0, 0);
    screen.setTextSize(1);
    
    screen_w = screen.width();
    screen_h = screen.height();

    // Set up the player scores and bat positions.
    score_p1    = 0;
    score_p2    = 0;
    position_p1 = 0;
    position_p2 = 0;

    // Set up the ball position and direction of travel.
    ball_pos_x  = screen_w/2;
    ball_pos_y  = screen_h/2;
    ball_dir_x  = ball_speed;
    ball_dir_y  = ball_speed;

    // Run the startup countdown.
    drawPlayerScores();
    drawPlayerBats();
    startCountdown();
}

void updateBall()
{
    // First, rub out the previous ball we drew.
    screen.fill(255,255,255);
    screen.stroke(255,255,255);
    screen.circle(ball_pos_x, ball_pos_y, ball_size);

    // Now let's update where the ball should be.

    // Should it bounce of the walls?
    if(ball_pos_y > screen_h)
    {
        ball_dir_y = -ball_speed;
    } 
    else if (ball_pos_y < 0)
    {
        ball_dir_y  = ball_speed;
    }

    // Should it bounce off player 1's bat?
    if(ball_pos_x < bat_w &&
       ball_pos_y > position_p1 &&
       ball_pos_y < position_p1 + bat_h)
    {
        ball_dir_x = ball_speed;
    }
    // Should it bounce off player 2's bat?
    else if(ball_pos_x > screen_w - bat_w &&
       ball_pos_y > position_p2 &&
       ball_pos_y < position_p2 + bat_h)
    {
        ball_dir_x = -ball_speed;
    }
    // Has player one scored?
    else if (ball_pos_x > screen_w)
    {
        // increase player one's score
        score_p1 += 1;
        // reset the ball position to the middle of the screen.
        ball_pos_x = screen_w/2;
        ball_pos_y = screen_h/2;
        ball_dir_x = -ball_dir_x;
    }
    // Has player two scored?
    else if(ball_pos_x < 0)
    {
        // increase player one's score
        score_p2 += 1;
        // reset the ball position to the middle of the screen.
        ball_pos_x = screen_w/2;
        ball_pos_y = screen_h/2;
        ball_dir_x = -ball_dir_x;
    }

    // Make the ball move in the right direction.
    ball_pos_x = ball_pos_x + ball_dir_x;
    ball_pos_y = ball_pos_y + ball_dir_y;

    // Now draw the new ball
    screen.fill  (0,0,255);     //What color shall the ball be?
    screen.circle(ball_pos_x, ball_pos_y, ball_size);
}

void drawPlayerBats()
{
    // Draw player 1's bat. First, clear the old area the bat took up.
    screen.fill(255,255,255);
    screen.stroke(255,255,255);
    screen.rect(1,position_p1,bat_w,bat_h);

    // Clear player 2's bat. How do we know the position of their bat?
    screen.rect(screen_w-4,position_p2,bat_w,bat_h);

    // Read the player positions. This changes position_p1 and position_p2
    getPlayerPositions();

    // Now we can draw the new bats
    // Draw player 1's bat first.
    screen.fill(0,255,0);       // Make player 1's bat green.
    screen.rect(1,position_p1,bat_w,bat_h);

    // Now draw player 2's bat. Remember, it needs to be on the other side
    // of the screen.
    screen.fill(255,0,0);       // Make player 2's bat red.
    screen.rect(screen_w-4,position_p2,bat_w,bat_h);
}

void drawPlayerScores()
{
    // This function will draw a very simple "X - Y" string where
    // X and Y are the scores for each player.

    // Set the text color to black.
    screen.stroke(0,0,0);
    screen.fill(255,255,255);

    // blank the previous position of the scores text.
    screen.rect(screen_w/2-17,0,40,10);

    // We will print six letters, so make our array six long.
    char toPrint[6];
    String S = "";
    S += String(score_p1);  // Add the player 1 score
    S += " - ";             // Separate the two scores
    S += String(score_p2);  // Add the player 2 score
    S.toCharArray(toPrint,6); // Convert the string to something we can show.
    screen.text(toPrint,screen_w/2-15,1);
}

void getPlayerPositions(){
    // Read player 1 position
    position_p1 = map(analogRead(PIN_P1_BAT),0,1023-bat_h,0,screen_h);
    
    // Read player 2 position
    position_p2 = map(analogRead(PIN_P2_BAT),0,1023-bat_h,0,screen_h);
}

void checkVictory()
{
    if(score_p1 >= 3)
    {
        // Make the font size nice and big.
        screen.setTextSize(2);

        // Print the message.
        screen.stroke(0,0,0);
        screen.text("Player 1 Wins!", 5,10);

        // Wait for a few seconds.
        delay (5000);
        setup();
    }
    else if(score_p2 >= 3)
    {
        screen.setTextSize(2);
        screen.stroke(0,0,0);
        screen.text("Player 2 Wins!", 5,10);
        delay (5000);
        setup();
    }

    // What shall we do now if someone has one? Can we call one function to
    // go back to the beginning again?
}

void loop() {

    // Draw the player scores.
    drawPlayerScores();

    // Draw the bats using the positions we read a moment ago.
    drawPlayerBats();

    // Draw and update the ball position.
    updateBall();

    // Check if anyone has won?
    checkVictory();
}
