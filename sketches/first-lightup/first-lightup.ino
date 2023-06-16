#include <Servo.h>

Servo servoMotor;
int initialPosition = 0;      // Initial position (0 degrees)
int targetPosition = 75;      // Target position (30 degrees)
int delayTime = 3000;        // Delay time in milliseconds (30 seconds)
int buttonPin = 8;            // Push button pin
int buttonState = 0;          // Current button state
int previousButtonState = 0;  // Previous button state
int redLightPin = 4;
int blueLightPin = 2;
int servoPin = 9;
int redLightState = 0;

void setup() {
  servoMotor.attach(servoPin);
  pinMode(buttonPin, INPUT);
  pinMode(redLightPin, OUTPUT);
  pinMode(blueLightPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Check button state
  buttonState = digitalRead(buttonPin);

  // Run servo motor code only when the button is pressed
  if (buttonState == HIGH && previousButtonState == LOW) {
    // Move to target position
    digitalWrite(redLightPin, HIGH);


    servoMotor.write(targetPosition);
    delay(delayTime);
    digitalWrite(redLightPin, LOW);
    // Move back to initial position
    digitalWrite(blueLightPin, HIGH);

    servoMotor.write(initialPosition);
    delay(delayTime);
    digitalWrite(blueLightPin, LOW);
  }

  delay(100);
  
  if (buttonState == HIGH) {
    Serial.println("presed");
  }
  
  previousButtonState = buttonState;
  
}
