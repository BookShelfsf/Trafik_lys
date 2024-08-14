// Pin Definitions
const int buttonPin = 2; // Button connected to digital pin 2
const int redPin1 = 11;  // Red LED 1
const int yelPin1 = 10;  // Yellow LED 1
const int grnPin1 = 9;   // Green LED 1
const int redPin2 = 3;   // Red LED 2
const int yelPin2 = 5;   // Yellow LED 2
const int grnPin2 = 6;   // Green LED 2

// Timing Variables
const unsigned long phaseDuration = 2000;        // Duration for each phase (2 seconds)
const unsigned long shortPhaseDuration = 500;    // Shorter duration for the transition (0.5 seconds)
bool sequenceStarted = false; // Flag to indicate if the sequence has started

void setup() {
  // Configure LED pins as outputs
  pinMode(redPin1, OUTPUT);
  pinMode(yelPin1, OUTPUT);
  pinMode(grnPin1, OUTPUT);

  pinMode(redPin2, OUTPUT);
  pinMode(yelPin2, OUTPUT);
  pinMode(grnPin2, OUTPUT);

  // Configure button pin as input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Initial state: All LEDs off
  allLedsOff();
}

void loop() {
  // Check if the button is pressed
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && !sequenceStarted) {
    redLight2();  // Turn on RedLight2 immediately
    sequenceStarted = true; // Start the sequence
    delay(2); // Debounce delay
  }

  // Run the sequence if it has started
  if (sequenceStarted) {
    // Light Set 1
    redLight1();          // Red only
    delay(phaseDuration);
    redYellowLight1();    // Red and Yellow
    delay(phaseDuration);
    greenLight1();        // Green only
    delay(phaseDuration);
    yellowLight1();       // Yellow only
    delay(phaseDuration);
    redLight1();          // Back to Red
    delay(shortPhaseDuration);  // Short delay before switching to the other set

    // Light Set 2
    redLight2();          // Red only
    delay(phaseDuration);
    redYellowLight2();    // Red and Yellow
    delay(phaseDuration);
    greenLight2();        // Green only
    delay(phaseDuration);
    yellowLight2();       // Yellow only
    delay(phaseDuration);
    redLight2();          // Back to Red
    delay(shortPhaseDuration);  // Short delay before switching to the other set
  }
}

// Functions to control LEDs for Light Set 1
void redLight1() {
  digitalWrite(redPin1, HIGH);  // Red on
  digitalWrite(yelPin1, LOW);   // Yellow off
  digitalWrite(grnPin1, LOW);   // Green off
}

void redYellowLight1() {
  digitalWrite(redPin1, HIGH);  // Red on
  digitalWrite(yelPin1, HIGH);  // Yellow on
  digitalWrite(grnPin1, LOW);   // Green off
}

void greenLight1() {
  digitalWrite(redPin1, LOW);   // Red off
  digitalWrite(yelPin1, LOW);   // Yellow off
  digitalWrite(grnPin1, HIGH);  // Green on
}

void yellowLight1() {
  digitalWrite(redPin1, LOW);   // Red off
  digitalWrite(yelPin1, HIGH);  // Yellow on
  digitalWrite(grnPin1, LOW);   // Green off
}

// Functions to control LEDs for Light Set 2
void redLight2() {
  digitalWrite(redPin2, HIGH);  // Red on
  digitalWrite(yelPin2, LOW);   // Yellow off
  digitalWrite(grnPin2, LOW);   // Green off
}

void redYellowLight2() {
  digitalWrite(redPin2, HIGH);  // Red on
  digitalWrite(yelPin2, HIGH);  // Yellow on
  digitalWrite(grnPin2, LOW);   // Green off
}

void greenLight2() {
  digitalWrite(redPin2, LOW);   // Red off
  digitalWrite(yelPin2, LOW);   // Yellow off
  digitalWrite(grnPin2, HIGH);  // Green on
}

void yellowLight2() {
  digitalWrite(redPin2, LOW);   // Red off
  digitalWrite(yelPin2, HIGH);  // Yellow on
  digitalWrite(grnPin2, LOW);   // Green off
}

// Function to turn off all LEDs
void allLedsOff() {
  digitalWrite(redPin1, LOW);
  digitalWrite(yelPin1, LOW);
  digitalWrite(grnPin1, LOW);
  
  digitalWrite(redPin2, LOW);
  digitalWrite(yelPin2, LOW);
  digitalWrite(grnPin2, LOW);
}
