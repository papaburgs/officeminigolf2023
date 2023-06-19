#include <LiquidCrystal.h>
#include <Wire.h>

#define I2C_DISP_ADDR 10

//const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

void setup() {
    Serial.begin(9600);
    Wire.begin(MY_I2C_ADDR);
    Serial.print("-----------------I am display device at " + MY_I2C_ADDR);           
    Wire.onReceive(receiveEvents);
  lcd.begin(16, 2);
  lcd.print("reboot         ");
  lcd.setCursor(0,1);
  lcd.print("                 ");
}

void loop() {
    delay(25);
}

void receiveEvents(int numBytes)
{   lcd.setCursor(0,0);
    char n;
    int row = -1;
    Serial.println("---> recieved events");
    Serial.println(numBytes);
    if (numBytes == 0) { 
        lcd.setCursor(0,0);
        lcd.print("empty message");
        Serial.println("empty message - abort");
    }
    if (numBytes > 16) { 
        Serial.println("long message - will be cut off");
    }

    n = Wire.read();
    if (n == '1') {
        lcd.setCursor(0,0);
        Serial.println("destined for first row");
    } 
    if ( n == '2') {
        lcd.setCursor(0,1);
        Serial.println("destined for second row");
    }
    Serial.println("got a message: ");
    for ( int i=1; i<numBytes; i++){
        n = Wire.read();
        Serial.print(n);
        lcd.write(n);
    }
    int leftover = 16-numBytes;
    while  (leftover >= 0) {
      lcd.write(" ");
      leftover--;
    }
    Serial.println("");
    Serial.println("--------------------------------");
}
    
