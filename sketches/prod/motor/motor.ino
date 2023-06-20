#include <Wire.h>
#include <Stepper.h>
#include <Servo.h>


const int I2C_DISP_ADDR=10;
const int I2C_MOTOR_ADDR=11;
const int GATEOPEN = 0;
const int GATECLOSE = 1;

// these are signals from the controller
const int MTR_DISPENSE=1;
const int MTR_OPEN=2;
const int MTR_CLOSE=3;

Servo myservo; 

const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10,9, 11);
const int buttonD = 2;
const int buttonG = 3;

// gateState uses the defined const above
int gateState;


void setup() {
  Serial.begin(9600);
  Serial.println("----- Motor driver"); 
  pinMode(buttonG, INPUT);
  pinMode(buttonD, INPUT);
  myservo.attach(12); 
  closeGate();
  Wire.begin(I2C_MOTOR_ADDR);
  
  myStepper.setSpeed(25);        
  Wire.onReceive(receiveEvents);
}

void loop() {
  
  //Serial.println("loop");
  if (digitalRead(buttonD) == HIGH) {
    Serial.println("deploying");
    rotate();
    Serial.println("delay");
    delay(500);
  }

  if (digitalRead(buttonG) == HIGH) {
    Serial.println("gate");
    if (gateState == GATEOPEN) {
      closeGate();
    } else {
      openGate();
    }
    delay(500);
  }
  
  delay(25);
}
void receiveEvents(int numBytes) {  
  Serial.println("---> recieved events");
  Serial.println(numBytes);
  delay(1000);

  int n;
  n = Wire.read();
  Serial.println(n);
  delay(5000);
  switch (n) {
    case MTR_DISPENSE:
      Serial.println("want to send");
      //rotate();
       myStepper.step(-stepsPerRevolution);
      break;
    case MTR_OPEN:
      openGate();
      break;
    case MTR_CLOSE:
      closeGate();
      break;
    default:
      Serial.println("unknown");
      break;
  }
  Serial.println("switch done");
  delay(150);
}

void rotate() {
  Serial.println("sending steps");
  myStepper.step(-stepsPerRevolution);
}

void openGate() {
  Serial.println("opening gate");
  int pos;
  for (pos = 30; pos >= 0; pos -= 2) { 
   // myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.write(0);
  Serial.println("gateopened");
  gateState = GATEOPEN;  
}

void closeGate() {
  Serial.println("close gate");
  int pos;
  for (pos = 0; pos <= 30; pos += 2) { 
   // myservo.write(pos);              
    delay(15);
  }
  myservo.write(30);
  Serial.println("gate closed");
  gateState = GATECLOSE;
}