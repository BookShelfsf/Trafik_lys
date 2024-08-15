// Pin Definitions
const int startButtonPin = 2;  // Button connected to digital pin 2 for starting the sequence
const int resetButtonPin = 4;  // Button connected to digital pin 4 for resetting the lights to red
const int redPin1 = 11;        // Red LED 1 (also stays on initially and after sequence stops)
const int yelPin1 = 10;        // Yellow LED 1
const int grnPin1 = 9;         // Green LED 1
const int redPin2 = 3;         // Red LED 2 (also stays on initially and after sequence stops)
const int yelPin2 = 5;         // Yellow LED 2
const int grnPin2 = 6;         // Green LED 2

// Timing Variables
const unsigned long phaseDuration = 2000;        // Duration for each phase (2 seconds)
const unsigned long shortPhaseDuration = 500;    // Shorter duration for the transition (0.5 seconds)
volatile bool sequenceStarted = false;           // Flag to indicate if the sequence has started
int lastStartButtonState = HIGH;  // Variable to store the last state for the start button
int lastResetButtonState = HIGH;  // Variable to store the last state of the reset button

void setup() {
  // Configure LED pins as outputs
  pinMode(redPin1, OUTPUT);
  pinMode(yelPin1, OUTPUT);
  pinMode(grnPin1, OUTPUT);

  pinMode(redPin2, OUTPUT);
  pinMode(yelPin2, OUTPUT);
  pinMode(grnPin2, OUTPUT);

  // Configure button pins as input with pull-up resistors
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);

  // Initialize serial communication
  Serial.begin(9600);

  // Turn off all LEDs and keep redPin2 and redPin1 on initially
  allLedsOff();
  digitalWrite(redPin1, HIGH);
  digitalWrite(redPin2, HIGH);
}

void loop() {
  // Read the state of the start button
  int startButtonState = digitalRead(startButtonPin);
  if (startButtonState == LOW && lastStartButtonState == HIGH) {
    // Debounce delay
    delay(50);
    if (!sequenceStarted) {
      sequenceStarted = true; // Start the sequence if it is not already started
    }
  }
  lastStartButtonState = startButtonState;

  // Read the state of the reset button
  int resetButtonState = digitalRead(resetButtonPin);
  if (resetButtonState == LOW && lastResetButtonState == HIGH) {
    // Debounce delay
    delay(50);
    resetToRed(); // Reset all lights to red
    sequenceStarted = false; // Stop the sequence
  }
  lastResetButtonState = resetButtonState;

  // If the sequence has started, run the sequence
  if (sequenceStarted) {
    runSequence();
  } else {
    // If the sequence is not started, ensure all LEDs are off except redPin1 and redPin2
    allLedsOff();
    digitalWrite(redPin1, HIGH);
    digitalWrite(redPin2, HIGH);
  }
}

// Function to run the sequence
void runSequence() {
  // Light Set 1
  redLight1();
  delayCheck(phaseDuration);

  redYellowLight1();
  delayCheck(phaseDuration);

  greenLight1();
  delayCheck(phaseDuration);

  yellowLight1();
  delayCheck(phaseDuration);

  redLight1();
  delayCheck(shortPhaseDuration);

  // Light Set 2
  redLight2();
  delayCheck(phaseDuration);

  redYellowLight2();
  delayCheck(phaseDuration);

  greenLight2();
  delayCheck(phaseDuration);

  yellowLight2();
  delayCheck(phaseDuration);

  redLight2();
  delayCheck(shortPhaseDuration);
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

// Function to reset all lights to red
void resetToRed() {
  digitalWrite(redPin1, HIGH);
  digitalWrite(yelPin1, LOW);
  digitalWrite(grnPin1, LOW);
  digitalWrite(redPin2, HIGH);
  digitalWrite(yelPin2, LOW);
  digitalWrite(grnPin2, LOW);
}

void delayCheck(unsigned long duration) {
  unsigned long startTime = millis();
  while (millis() - startTime < duration) {
    if (digitalRead(resetButtonPin) == LOW) {
      resetToRed(); // Reset all lights to red
      sequenceStarted = false; // Stop the sequence
      return; // Exit the function
    }
    // Optionally, add a small delay to avoid high CPU usage
    delay(10); //
  }
}
