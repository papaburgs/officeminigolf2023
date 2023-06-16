#include <Wire.h>
//#include <Stepper.h>
//#include <Servo.h>

//# define I2C_ADDRESS 11

const int GATEOPEN = 0;
const int GATECLOSE = 1;

//Servo myservo; 

const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
//Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
const int buttonD = 2;
const int buttonG = 3;

// gateState uses the defined const above
int gateState;


void setup() {
  //myStepper.setSpeed(15);
  Serial.begin(9600);
  pinMode(buttonG, INPUT);
  pinMode(buttonD, INPUT);
  //myservo.attach(12); 
  closeGate();
  Wire.begin(11);
  Serial.println("-----------------I am Slave1");           
  Wire.onReceive(receiveEvents);
}

void loop() {
  /*
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
  */
  delay(25);
}
void receiveEvents(int numBytes)
{  
  Serial.println("---> recieved events");
  char n;
  n = Wire.read();
  if (n == 'D') {
    rotate();
    return;
  }
  if (n == 'O') {
    openGate();
    return;
  }
 if (n == 'C') {
    closeGate();
    return;
  }
  Serial.println("Recieved unknown byte:");
  Serial.println(n);
}

void rotate() {
  Serial.println("deploying");
   //myStepper.step(-stepsPerRevolution);
}

void openGate() {
  Serial.println("opening gate");
  int pos;
  for (pos = 30; pos >= 0; pos -= 2) { 
   // myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  //myservo.write(0);
  gateState = GATEOPEN;  
}

void closeGate() {
  Serial.println("close gate");
  int pos;
  for (pos = 0; pos <= 30; pos += 2) { 
   // myservo.write(pos);              
    delay(15);
  }
  //myservo.write(30);
  gateState = GATECLOSE;
}