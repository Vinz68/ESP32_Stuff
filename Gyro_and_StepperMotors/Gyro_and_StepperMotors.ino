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
#include "Arduino.h"
#include "heltec.h"
#include <TinyMPU6050.h>
#include "images.h"

// DRV8825 GPIO Pins
#define MOTOR1_STEP 1   // GPIO 1
#define MOTOR1_DIR 3    // GPIO 3

// Constructing MPU-6050 
MPU6050 mpu (Wire1);

// Angle data 
float angX, angY, angZ;
bool firstRun = true;


/* Method that prints everything */
void PrintGets () {
  // Shows offsets
  Serial.println("--- Offsets:");
  Serial.print("GyroX Offset = ");
  Serial.println(mpu.GetGyroXOffset());
  Serial.print("GyroY Offset = ");
  Serial.println(mpu.GetGyroYOffset());
  Serial.print("GyroZ Offset = ");
  Serial.println(mpu.GetGyroZOffset());
  // Shows raw data
  Serial.println("--- Raw data:");
  Serial.print("Raw AccX = ");
  Serial.println(mpu.GetRawAccX());
  Serial.print("Raw AccY = ");
  Serial.println(mpu.GetRawAccY());
  Serial.print("Raw AccZ = ");
  Serial.println(mpu.GetRawAccZ());
  Serial.print("Raw GyroX = ");
  Serial.println(mpu.GetRawGyroX());
  Serial.print("Raw GyroY = ");
  Serial.println(mpu.GetRawGyroY());
  Serial.print("Raw GyroZ = ");
  Serial.println(mpu.GetRawGyroZ());
  // Show readable data
  Serial.println("--- Readable data:");
  Serial.print("AccX = ");
  Serial.print(mpu.GetAccX());
  Serial.println(" m/s²");
  Serial.print("AccY = ");
  Serial.print(mpu.GetAccY());
  Serial.println(" m/s²");
  Serial.print("AccZ = ");
  Serial.print(mpu.GetAccZ());
  Serial.println(" m/s²");
  Serial.print("GyroX = ");
  Serial.print(mpu.GetGyroX());
  Serial.println(" degrees/second");
  Serial.print("GyroY = ");
  Serial.print(mpu.GetGyroY());
  Serial.println(" degrees/second");
  Serial.print("GyroZ = ");
  Serial.print(mpu.GetGyroZ());
  Serial.println(" degrees/second");
  // Show angles based on accelerometer only
  Serial.println("--- Accel angles:");
  Serial.print("AccelAngX = ");
  Serial.println(mpu.GetAngAccX());
  Serial.print("AccelAngY = ");
  Serial.println(mpu.GetAngAccY());
  // Show angles based on gyroscope only
  Serial.println("--- Gyro angles:");
  Serial.print("GyroAngX = ");
  Serial.println(mpu.GetAngGyroX());
  Serial.print("GyroAngY = ");
  Serial.println(mpu.GetAngGyroY());
  Serial.print("GyroAngZ = ");
  Serial.println(mpu.GetAngGyroZ());
  // Show angles based on both gyroscope and accelerometer
  Serial.println("--- Filtered angles:");
  Serial.print("FilteredAngX = ");
  Serial.println(mpu.GetAngX());
  Serial.print("FilteredAngY = ");
  Serial.println(mpu.GetAngY());
  Serial.print("FilteredAngZ = ");
  Serial.println(mpu.GetAngZ());
  // Show filter coefficients
  Serial.println("--- Angle filter coefficients:");
  Serial.print("Accelerometer percentage = ");
  Serial.print(mpu.GetFilterAccCoeff());
  Serial.println('%');
  Serial.print("Gyroscope percentage = ");
  Serial.print(mpu.GetFilterGyroCoeff());
  Serial.println('%');
}

/* Show info on OLED */
void logo(){
  Heltec.display->clear();
  Heltec.display->drawXbm(0, 0, logo_width, logo_height, (const unsigned char *)logo_bits);
  Heltec.display->drawString(16, 42, "Sensor_MPU-6050");
  Heltec.display->drawString(35, 53, "Version 0.1");
  Heltec.display->display();
}


void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
  logo();
  delay(5000);
  Heltec.display->clear();

  Wire1.begin(SDA, SCL);   // Scan the device address via I2C1

  // Initialization
  mpu.Initialize();

  // Calibration
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  mpu.Calibrate();
  Serial.println("Calibration complete!");
  Heltec.display->clear();
  Heltec.display->display();
}

void loop() {
  mpu.Execute();

  if (firstRun)
  {
    PrintGets();
    firstRun = false;
    return;
  }

  // Get X,Y,Z angels and display on OLED
  angX = mpu.GetAngX();
  angY = mpu.GetAngY();
  angZ = mpu.GetAngZ();

  Heltec.display->clear();
  Heltec.display->drawString(16, 10, "AngX = "+ String(angX));  
  Heltec.display->drawString(16, 22, "AngY = "+ String(angY));  
  Heltec.display->drawString(16, 34, "AngZ = "+ String(angZ));  
  Heltec.display->display();
 
}
