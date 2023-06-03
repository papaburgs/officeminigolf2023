# Keypad notes

## old one
I have an old keypad from 30 years ago, doesn't work the same, may work but will take some tinkering

## from kit
seems to work, just flimsy

* 8 lines, from left to right when keypad is up
* first 4 are rows, last four are columns

### Code
```
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
byte pin_rows[ROW_NUM] = {9,8,7,6}; // Connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5,4,3,2}; // Connect to the column pinouts of the keypad

// Create an instance of the Keypad class
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);



void setup() {
 
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // non-blocking
  char key = keypad.getKey();
  
  if (key) {
    Serial.println(key);
  }
  delay(100);
}
```
