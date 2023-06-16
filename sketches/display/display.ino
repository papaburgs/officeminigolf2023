// Arduino pins connected to shift register
const int dataPin = 6;   // DS (Serial Data) yellow
const int latchPin = 8;  // ST_CP (Latch) white
const int clockPin = 7;  // SH_CP (Clock) black

// Define the segments for each digit (0-9)
const byte segmentData[] = {
  B01111110,  // 0
  B00110000,  // 1
  B01101101,  // 2
  B01111001,  // 3
  B00110011,  // 4
  B01011011,  // 5
  B01011111,  // 6
  B01110000,  // 7
  B01111111,  // 8
  B01110011   // 9
};

void setup() {
  // Set shift register pins as outputs
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  /*
     digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 255);
    digitalWrite(latchPin, HIGH);
    Serial.println("hold");
    delay(5000); 
    */
  /*
  for (int display = 0; display < 256; display++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, display);
    digitalWrite(latchPin, HIGH);
    Serial.println(display);
    delay(100); 
  }
  */
  for (int digit = 0; digit <= sizeof(segmentData); digit++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
    Serial.println(digit);
    delay(500);    
     digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
    
    delay(500); 

  }
  /*
   digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 255);
    digitalWrite(latchPin, HIGH);
    delay(1000); 
  */

  /*
  // Display each digit
  for (int digit = 0; digit < 4; digit++) {
    int digitValue = number % 10;  // Get the last digit
    
    // Shift out the segment data for the current digit
    shiftOut(dataPin, clockPin, LSBFIRST, segmentData[digitValue]);
    
    // Shift out the digit select value for the current digit
    shiftOut(dataPin, clockPin, LSBFIRST, ~(1 << digit));
    
    // Latch the data to the shift register outputs
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
    
    // Move to the next digit
    number /= 10;
    
    // Delay to control the display refresh rate
    delay(2);
  }
  */

}

