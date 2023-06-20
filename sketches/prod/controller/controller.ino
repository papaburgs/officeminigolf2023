#include <Keypad.h>
#include <Wire.h>

const int I2C_DISP_ADDR=10;
const int I2C_MOTOR_ADDR=11;

const int NUM_ROW=4;
const int NUM_COL=4;

const int MTR_DISPENSE=1;
const int MTR_OPEN=2;
const int MTR_CLOSE=3;

// Define the keymap
char keys[NUM_ROW][NUM_COL] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'}, 
    {'*', '0', '#', 'D'}
};

// Define the row and column pins of the keypad
//byte pin_rows[NUM_ROW] = {2,3,4,5}; // Connect to the row pinouts of the keypad
//byte pin_column[NUM_COL] = {6,7,8,9}; // Connect to the column pinouts of the keypad
byte pin_rows[NUM_ROW] = {9,8,7,6}; // Connect to the row pinouts of the keypad
byte pin_column[NUM_COL] = {5,4,3,2}; // Connect to the column pinouts of the keypad
// Create an instance of the Keypad class
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, NUM_ROW, NUM_COL);

bool debugOn;
// seed is what is displayed
String seed;

// seedSetTime is when the seed was last set
unsigned long seedSetTime;

// goodPin is the answer to a good pin
String goodPin;

// enteredPin is what user has put in so far
String enteredPin;

int bd = 0;
// gateOpened is the millis when gate was Opened
// set to zero when gate is closed
unsigned long gateOpened;

unsigned long gateOpenTimeout = 30000;

void setup() {  
    Wire.begin(); 							
    Serial.begin(9600); 	
    Serial.println("--------- Controller");
    keypad.setDebounceTime(50);
    gateOpened = 0;
    delay(100);
    updateSeed();
    delay(150);
}

void loop() {

    char key = keypad.getKey();
    if (key) {
        Serial.println("key entered: " + String(key));
        switch (key) {
            case '*':
                updateSeed();
                break;
            case '#':
                testInput();
                break;
            case 'D':
                dispenseBall();
                break;
            default:
                processKey(key);
                break;
        }
    }

    // check if we should close gate
    // if current milliseconds minus when the gate was opened 
    if (gateOpened != 0) {
        if (millis() - gateOpened > 30000) {
            closeGate();
        }
    }
    delay(75);
}

void processKey(char key)  {
  /*
    if (bd == 0 || bd == 3) {
        if (key == 'B') {
            bd++;
            Serial.println("bd - b");
        }
    }

    if (bd == 1 || bd == 2) {
        if (key == '0') {
            bd++;
            Serial.println("bd - 0");
        }
    }

    if ( bd == 4 && key == '5') {
        debugOn == true;
        bd++;
        Serial.println("bd - on");
    }
    */
    enteredPin += key;
    Serial.println(key);
    Wire.beginTransmission(I2C_DISP_ADDR);
    Wire.print("2Pin: "+enteredPin+"         ");											
    Wire.endTransmission(); 		
}

void testInput() {
    Serial.println("testing");
    if (enteredPin == goodPin) {
        Serial.println("opening gate");
        openGate();
    } else {
        Wire.beginTransmission(I2C_DISP_ADDR);
        Wire.print("1 Error          ");											
        Wire.endTransmission(); 		
        delay(100);
        Wire.beginTransmission(I2C_DISP_ADDR);
        Wire.print("2 Bad Pin        ");											
        Wire.endTransmission(); 	
        delay(100);	
    }
    //dispenseBall();
    delay(2000);
    updateSeed();
}

void updateSeed() {
    Serial.println("updating seed");
    reset();
    // find random number
    randomSeed(analogRead(A1)); 
    unsigned long randomNumber = random(10000,100000);
    seed = String(randomNumber);
    Serial.println(seed);
    // compute answer
    computeAnswer(randomNumber);
    delay(100);
    Wire.beginTransmission(I2C_DISP_ADDR);
    Wire.print("1Seed: "+seed+"          ");											
    Wire.endTransmission(); 
    delay(100);		
    Wire.beginTransmission(I2C_DISP_ADDR);
    Wire.print("2Pin:            ");											
    Wire.endTransmission(); 
    delay(100);			

}

void reset() {
  Serial.println("reseting");
    enteredPin = "";
    Wire.beginTransmission(I2C_DISP_ADDR);
    Wire.print("1 RESETTING... ");										
    Wire.endTransmission(); 
    delay(100);
    Wire.beginTransmission(I2C_DISP_ADDR);
    Wire.print("2 Please wait  ");											
    Wire.endTransmission(); 	
    delay(1500);

}

void dispenseBall() {
    Serial.println("Send ball");
    delay(500);
    Wire.beginTransmission(I2C_MOTOR_ADDR);
    Wire.write(MTR_DISPENSE);											
    Wire.endTransmission(); 
    delay(100);		
}

void closeGate() {
    gateOpened = 0;
    Wire.beginTransmission(I2C_MOTOR_ADDR);
    Wire.write(MTR_CLOSE);											
    Wire.endTransmission(); 		
}

void openGate() {
    gateOpened = millis();
    Wire.beginTransmission(I2C_MOTOR_ADDR);
    Wire.write(MTR_OPEN);											
    Wire.endTransmission(); 		
}

void computeAnswer(unsigned long seed) {
    // Divide the number by 11
    unsigned long r = floor(seed / 3);
    r *= 13;

    String rs = String(r);

    // Swap each pair of numbers
    int length = rs.length();
    for (int i = 0; i < rs.length() - 1; i += 2) {
        char temp = rs[i];
        rs[i] = rs[i + 1];
        rs[i + 1] = temp;
    }
  
    rs = rs.substring(rs.length()-4, rs.length());
    Serial.println("working pin: " + rs);
    goodPin = rs;
}

