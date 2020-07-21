
/*--------------------------------------------------------------------------------------------------------
 * StepperMotor_DRV88250 VibeSoft drives one stepper motor - using a DRV8825 motor driver 
 * -------------------------------------------------------------------------------------------------------
 * 
 * This code:
 * - Requires the library: TinyMPU6050 (Tools->Manage Library, search and install TinyMPU6050) 
 * - It outputs the same values as the library example: ArduinoIDE_All_Gets_Example 
 * 
 * This is a great start to use the MPU6050 on the ESP32 Development board
 * -------------------------------------------------------------------------------------------------------
*/
#include <Arduino.h>
//#include "heltec.h"
//#include <TinyMPU6050.h>
//#include "images.h"

// Define motor pin connections (for DRV8825)
const int dirPin = 3;
const int stepPin = 2;
const int faultPin = 4;

int val = 0;      // variable to store the read value

// Define motor's steps per revolution
const int stepsPerRevolution = 200;

void setup()
{
  //Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);

    Serial.begin (9600);      // only required for debugging. Output some settings in the Serial Monitor Window 
    
  // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(faultPin, INPUT);

  delay(2000);    
}
void loop()
{
  
  val = digitalRead(faultPin);   // read the input pin

  Serial.print("Fault = ");   
  Serial.println(val);

  Serial.println("Set motor direction clockwise");        
  // Set motor direction clockwise
  digitalWrite(dirPin, HIGH);


  Serial.println("Spin motor slowly");  
  // Spin motor slowly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(5000);
  }
  delay(1000); // Wait a second

  Serial.println("Set motor direction counterclockwise");    
  // Set motor direction counterclockwise
  digitalWrite(dirPin, LOW);

  Serial.println("Spin motor quickly");  
  // Spin motor quickly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(5000);
  }

  Serial.println("S Wait 5 seconds");      
  delay(5000); // Wait a second
}
