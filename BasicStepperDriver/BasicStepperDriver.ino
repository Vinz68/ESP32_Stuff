
/*--------------------------------------------------------------------------------------------------------
 * StepperMotor_DRV88250 VibeSoft drives one stepper motor - using a DRV8825 motor driver 
 * -------------------------------------------------------------------------------------------------------
 * 
 * Connect STEP, DIR as indicated
 * 
 * This is a great start to use the DRV88250 on the ESP32 Development board
 * -------------------------------------------------------------------------------------------------------
*/
#include "Arduino.h"
#include "heltec.h"
//#include <TinyMPU6050.h>
#include "images.h"
#include "BasicStepperDriver.h"

// Define motor pin connections (for DRV8825)
const int dirPin = 1;       // Direction
const int stepPin = 3;      // Step (pulse)
const int enablePin = 2;    // Enable/disable functionality
const int faultPin = 5;    // Fault (when false)

// Define motor's steps per revolution
const int stepsPerRevolution = 200;  // MOTOR_STEPS
const int RotationsPerMinute = 240;  // RPM


// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
const int microSteps = 1;            // MICROSTEPS 1

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(stepsPerRevolution, dirPin, stepPin,enablePin );

/* Show info on OLED */
void logo(){
  Heltec.display->clear();
  Heltec.display->drawXbm(0, 0, logo_width, logo_height, (const unsigned char *)logo_bits);
  Heltec.display->drawString(16, 42, "Motor_DRV8825");
  Heltec.display->drawString(35, 53, "Version 0.1");
  Heltec.display->display();
}



//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
  logo();
  delay(5000);
  Heltec.display->clear();

  // Calibration
  Serial.println("=====================================");
  Serial.println("Setup Stepper...");  

  // Initialization  
  stepper.begin(RotationsPerMinute, microSteps);
  
  // Using enable/disable on ENABLE pin (active LOW) 
  stepper.setEnableActiveState(LOW);
}

void loop() {

    Serial.println("Energize coils.");  
    // energize coils - the motor will hold position
    stepper.enable();

    delay(2000);
  
    /*
     * Moving motor one full revolution using the degree notation
     */
    Serial.println("Moving motor one full revolution using the degree notation");       
    stepper.rotate(360);

    delay(2000);

    /*
     * Moving motor to original position using steps
     */
    Serial.println("Moving motor to original position using steps");       
    stepper.move(-stepsPerRevolution*microSteps);

    delay(2000);

    Serial.println("pause and allow the motor to be moved by hand");    
    
    // pause and allow the motor to be moved by hand
    stepper.disable();

    delay(5000);
}
