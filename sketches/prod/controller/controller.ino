#include <Keypad.h>
#include <Wire.h>

#define I2C_DISP_ADDR 10
#define I2C_MOTOR_ADDR 11

#define NUM_ROW 4
#define NUM_COL 4

// Define the keymap
char keys[NUM_ROW][NUM_COL] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'}, 
    {'*', '0', '#', 'D'}
};

// Define the row and column pins of the keypad
byte pin_rows[NUM_ROW] = {2,3,4,5}; // Connect to the row pinouts of the keypad
byte pin_column[NUM_COL] = {6,7,8,9}; // Connect to the column pinouts of the keypad

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
    // just wondering what this will do, will it catch a type error
    gateOpened = -1;
    // gateOpened = 0;
    updateSeed();
    debugOn = false;
}

void loop() {

    char key = keypad.getKey();
    if (key) {
        Serial.println("key entered: " + key);
        switch (key) {
            case '*':
                updateSeed();
                break;
            case '#':
                testInput();
                break;
            case 'D':
                dispenseBall();
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
}

void processKey(char key)  {
    if (bd == 0 || bd == 3) {
        if (key == 'B') {
            bd++;
        }
    }

    if (bd == 1 || bd == 2) {
        if (key == '0') {
            bd++;
        }
    }

    if ( bd == 4 && key == '5') {
        debugOn == true;
        bd++;
    }
    enteredPin += key;
    Wire.beginTransmission(I2C_DISP_ADDR);
    Wire.print("1Pin: "+enteredPin+"         ");											
    Wire.endTransmission(); 		
}

void testInput() {
    if (enteredPin == goodPin) {
        openGate();
    } else {
        Wire.beginTransmission(I2C_DISP_ADDR);
        Wire.print("1 Error          ");											
        Wire.endTransmission(); 		
        delay(25);
        Wire.beginTransmission(I2C_DISP_ADDR);
        Wire.print("2 Bad Pin        ");											
        Wire.endTransmission(); 		
    }
    dispenseBall();
}

void updateSeed() {
    reset();
    // find random number
    randomSeed(analogRead(A0)); 
    int randomNumber = random(90000) + 10000; 
    seed = String(randomNumber);
    // compute answer
    computeAnswer(randomNumber);
    Wire.beginTransmission(I2C_DISP_ADDR);
    if (!debugOn) {
        Wire.print("2"+seed+"             ");											
    } else {
        Wire.print("2"+seed+"  --"+goodPin+"--    ");											
    } 

    Wire.endTransmission(); 		
    Wire.beginTransmission(I2C_DISP_ADDR);
    Wire.print("1Enter pin:              ");											
    Wire.endTransmission(); 		

}

void reset() {
    enteredPin = "";
    Wire.beginTransmission(I2C_DISP_ADDR);
    Wire.print("1 RESETTING...    ");											
    Wire.endTransmission(); 		
    Wire.beginTransmission(I2C_DISP_ADDR);
    Wire.print("2                 ");											
    Wire.endTransmission(); 		
    delay(1500);

}

void dispenseBall() {
    Serial.println("Send ball");
    Wire.beginTransmission(I2C_MOTOR_ADDR);
    Wire.write('D');											
    Wire.endTransmission(); 		
}

void closeGate() {
    gateOpened = 0;
    Wire.beginTransmission(I2C_MOTOR_ADDR);
    Wire.write('C');											
    Wire.endTransmission(); 		
}

void openGate() {
    gateOpened = millis();
    Wire.beginTransmission(I2C_MOTOR_ADDR);
    Wire.write('O');											
    Wire.endTransmission(); 		
}

void computeAnswer(int seed) {
    // Divide the number by 11
    int r = floor(seed / 3);
    r *= 13;

    String rs = String(r);
    Serial.println("after multipications: " + rs);
    // Swap each pair of numbers
    int length = rs.length();
    for (int i = 0; i < rs.length() - 1; i += 2) {
        char temp = rs[i];
        rs[i] = rs[i + 1];
        rs[i + 1] = temp;
    }

    Serial.println("after swaps: " + rs);
    // Extract the 4 least significant digits
  
    rs = rs.substring(0, 4);
    Serial.println("4 least sig digits: " + rs);
    goodPin = rs;
}

