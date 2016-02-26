
// These constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// Store whether the button is on or off here.
int buttonState = 0;

void setup() {
  // Initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // Initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // Check if the pushbutton is pressed.
  // If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // Turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // Turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
