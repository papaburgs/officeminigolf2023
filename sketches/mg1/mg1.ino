#include <Stepper.h>
#include <Servo.h>


// stepper config
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// Pin definitions for shift registers
const int dataPin = 2;    // Arduino pin connected to data pin of first shift register
const int latchPin = 3;   // Arduino pin connected to latch pin of first shift register
const int clockPin = 4;   // Arduino pin connected to clock pin of first shift register

int correctPin = 1234;
int enteredPin = 0000;

const byte digitPatterns[] = {
    B11111100,  // 0
    B01100000,  // 1
    B11011010,  // 2
    B11110010,  // 3
    B01100110,  // 4
    B10110110,  // 5
    B10111110,  // 6
    B11100000,  // 7
    B11111110,  // 8
    B11100110   // 9
};

// define servo features
Servo myservo;
const int gateClosedPos = 10;
const int gateOpenPos = 45;
const int servoPin = 1;

void setup() {
    // Initialize the shift register pins
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    // setup stepper
    myStepper.setSpeed(60);

    // setup servo
    servoMotor.attach(servoPin);

    // Enable Serial
    Serial.begin(9600);

}

void loop() {
}


void resetSeed () {
    // TODO, make this a random 4 digit
    correctPin = 1234;
    enteredPin = 0000;
}

void addDigit(int next) {
    enteredPin = enteredPin * 10 + next;
    if (enteredPin > 9999) {
        enteredPin = enteredPin - 10000;
    }
}

// Function to update the 4 x 7-segment display
void updateDisplay(int digit, int position) {
    // Error checking for valid digit and position values
    if (digit < 0 || digit > 9 || position < 0 || position > 3) {
        // Invalid digit or position, do nothing
        return;
    }

    // Calculate the shift register data for the given digit
    byte shiftData = digitPatterns[digit];

    // Determine the digit selection pattern based on position
    byte digitSelection = 1 << position;

    // need to test out this part, not sure it will work
    // Send the digit selection pattern to the second shift register
    digitalWrite(latchPin, LOW);  // Start data transfer
    shiftOut(dataPin, clockPin, MSBFIRST, digitSelection);  // Send the data
    digitalWrite(latchPin, HIGH); // End data transfer

    // Send the shift register data to the first shift register
    digitalWrite(latchPin, LOW);  // Start data transfer
    shiftOut(dataPin, clockPin, MSBFIRST, shiftData);  // Send the data
    digitalWrite(latchPin, HIGH); // End data transfer
}

void dispence() {
    // rotate stepper 360 degrees
    Serial.println("rotate wheel");
    myStepper.step(-200);
}

void openGate() {
    servoMotor.write(targetPosition);
    for (pos = gateClosedPos; pos <= gateOpenPos; pos += 1) { 
        myservo.write(pos); 
        delay(10);         
    }
}

void closeGate() {
    servoMotor.write(targetPosition);
    for (pos = gateOpenPos; pos >= gateClosePos; pos -= 1) { 
        myservo.write(pos);
        delay(
                }
                }


