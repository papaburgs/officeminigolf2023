#include <Wire.h>
# define I2C_DISP_ADDR 10

void setup()
{
 	Wire.begin(); 							
 	Serial.begin(9600); 	
 	Serial.println(F("---------------I am the Master\n"));
 	delay(1000);
}

void loop()
{
 	delay(5000);
  Serial.println("sending message");
 	Wire.beginTransmission(I2C_DISP_ADDR);
 	Wire.print("1first msg (t).......");											
 	Wire.endTransmission(); 		
 	Serial.println("");

 	delay(5000);
  Serial.println("message 2");
 	Wire.beginTransmission(I2C_DISP_ADDR);
 	Wire.print("2second msg (b)........");										
 	Wire.endTransmission(); 		
 	Serial.println("");

	delay(5000);
  Serial.println("sending third message");
 	Wire.beginTransmission(I2C_DISP_ADDR);
 	Wire.print("2third msg(b)");											
 	Wire.endTransmission(); 		
 	Serial.println("");

   	delay(5000);
  Serial.println("sending last");
 	Wire.beginTransmission(I2C_DISP_ADDR);
 	Wire.print("1last msg (t)");											
 	Wire.endTransmission(); 		
 	Serial.println("");
}
