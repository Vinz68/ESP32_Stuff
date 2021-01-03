/*--------------------------------------------------------------------------------------------------------
 * Sensor_MPU9250 : Outputs the values of the MPU-9250 sensor.
 * The MPU-9250 is a multi-chip module (MCM) consisting of:
- 3-Axis accelerometer
- 3-Axis gyroscope
- 3-Axis magnetometer
 * -------------------------------------------------------------------------------------------------------
 * 
 * This code:
 * - Requires the library: MPU9250_asukiaaa (Tools->Manage Library, search and install MPU9250_asukiaaa) 
 * 
 * -------------------------------------------------------------------------------------------------------
*/
/*
 * MPU-9250     Type      ESP32 / GPIO      pin on ESP32
  VCC           3.3V      3.3 V             3nd top right (usb up)
  GND           Ground    GND               1st top right
  SCL           Clock     SCL I2C1          GPIO 22 - 2nd last right  
  SDA           Data      SDA I2C1          GPIO 21 - last right   
  INT           Interrupt                   GPIO 2  - 8th from top right
 */


#include "heltec.h"
#include "images.h"
#include <MPU9250_asukiaaa.h>

#define SDA_PIN 21
#define SCL_PIN 22

MPU9250_asukiaaa MpuSensor;
float aX, aY, aZ, aSqrt;
float gX, gY, gZ;
float mX, mY, mZ, mDirection;

static uint32_t prev_ms;
uint8_t sensorId;


void logo(){
  Heltec.display -> clear();
  Heltec.display -> drawXbm(0,0,logo_width,logo_height,(const unsigned char *)logo_bits);
  Heltec.display -> drawString( 8, 42, "MPU9250_VibeSoft"); 
  Heltec.display -> drawString(35, 53, "Version 0.4");   
  Heltec.display -> display();
}

void setup()
{
  // Initialize the Wifi_Kit_32 with its OLED and enable Serial port on 115200 baud.
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
  Serial.println("Setup started & Heltec ESP332 initialized");
  
  Serial.println("Show Logo...");  
  logo();

  delay(2000);
  Heltec.display->clear();

  Serial.println("Wire.Begin...");  
#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  MpuSensor.setWire(&Wire);
#endif

  Serial.println("MPU9250 Setup...");
  MpuSensor.beginAccel();
  MpuSensor.beginGyro();
  MpuSensor.beginMag();

  // You can set your own offset for mag values
  // MpuSensor.magXOffset = -50;
  // MpuSensor.magYOffset = -55;
  // MpuSensor.magZOffset = -10;

  delay(3000);
  
  if (MpuSensor.readId(&sensorId) == 0) {
    Serial.println("sensorId: " + String(sensorId));
  } else {
    Serial.println("Cannot read sensorId");
  }  

  prev_ms = millis();
  Serial.println("Setup ended.");
}

void loop()
{
    // Every 250 msec => output the sensor values
    if ((millis() - prev_ms) >= 250)
    {
        prev_ms = millis();
        Serial.print(String(millis()) + "ms : ");
      
        if (MpuSensor.accelUpdate() == 0) {
          aX = MpuSensor.accelX();
          aY = MpuSensor.accelY();
          aZ = MpuSensor.accelZ();
          aSqrt = MpuSensor.accelSqrt();
  
          Serial.print("accel X,Y,Z: ");
          Serial.print(aX);
          Serial.print(" , ");
          Serial.print(aY);
          Serial.print(" , ");
          Serial.print(aZ);
          Serial.print("  aSqrt: "); 
          Serial.print(aSqrt); 
        } else {
          Serial.println("Cannot read ACCEL values");
        }        
            

        if (MpuSensor.gyroUpdate() == 0) {
          gX = MpuSensor.gyroX();
          gY = MpuSensor.gyroY();
          gZ = MpuSensor.gyroZ();
          Serial.print("  gyro X,Y,Z: ");
          Serial.print(gX);
          Serial.print(" , ");
          Serial.print(gY);
          Serial.print(" , ");
          Serial.print(gZ);      
        } else {
          Serial.println("Cannot read GYRO values");
        }        

        if (MpuSensor.magUpdate() == 0) {
          mX = MpuSensor.magX();
          mY = MpuSensor.magY();
          mZ = MpuSensor.magZ();
          mDirection = MpuSensor.magHorizDirection();
          Serial.print("  Mag X,Y,Z: ");
          Serial.print(mX);
          Serial.print(" , ");
          Serial.print(mY);
          Serial.print(" , ");
          Serial.print(mZ); 
          Serial.println(" horizontal direction: " + String(mDirection));
        } else {
          Serial.println("Cannot read MAG values");
        }
    }
}
