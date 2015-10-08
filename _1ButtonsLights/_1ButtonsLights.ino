// Here we define which pins are which
#define BUTTON_PIN 5
#define LED_PIN 13

/*
  This function runs once when you first turn the Arduino on. 
  It sets up which pins we are going to use for inputs and outputs.
 */
void setup()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

/*
  After the setup function finishes, this one loops round and round 
  until we turn the Arduino off again.
 */
void loop()
{
  // Check if the buttons are pressed. This is how you check if any
  // pin is turned on.
  int button1 = digitalRead(BUTTON_PIN);

  // if it is pressed, turn on light number 1
  if(button1 == HIGH)
  {
    // This is how we turn a pin on. We call turning it on "setting it high"
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    // Again, this is how we turn a pin off. Called "setting it low"
    digitalWrite(LED_PIN, LOW);
  }
}

