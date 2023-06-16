#include <Keypad.h>

const int ROW_NUM = 4; // Number of rows in the keypad
const int COLUMN_NUM = 4; // Number of columns in the keypad

// Define the keymap
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'}, 
  {'*', '0', '#', 'D'}
};

// Define the row and column pins of the keypad
byte pin_rows[ROW_NUM] = {2,3,4,5}; // Connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {6,7,8,9}; // Connect to the column pinouts of the keypad

// Create an instance of the Keypad class
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);



void setup() {  
 
  Serial.begin(9600); // Initialize serial communication
Serial.println("start");
};
void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.println("key press");
    Serial.println(key);
  
  }
  delay(100);
  
}
