#include "heltec.h"
#include "WiFi.h"
#include "images.h"
#include <MPU9250_asukiaaa.h>

#define SDA_PIN 21
#define SCL_PIN 22

MPU9250_asukiaaa MpuSensor;
float aX, aY, aZ, aSqrt;
float gX, gY, gZ;
float mX, mY, mZ, mDirection;

void logo(){
  Heltec.display -> clear();
  Heltec.display -> drawXbm(0,0,logo_width,logo_height,(const unsigned char *)logo_bits);
  Heltec.display -> drawString( 8, 42, "MPU9250_VibeSoft"); 
  Heltec.display -> drawString(35, 53, "Version 0.3");   
  Heltec.display -> display();
}

void setup()
{
  // Initialize the Wifi_Kit_32 with its OLED and enable Serial port on 115200 baud.
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
  Serial.println("Setup started & Heltec ESP332 initialized");
  
  Serial.println("Show Logo...");  
  logo();

  Serial.println("Wire.Begin...");  
  Wire.begin(SDA_PIN, SCL_PIN);

  delay(3000);
  Heltec.display->clear();

  Serial.println("MPU9250 Setup...");
  MpuSensor.setWire(&Wire);  
  MpuSensor.beginAccel();
  MpuSensor.beginGyro();
  MpuSensor.beginMag();

  // You can set your own offset for mag values
  // MpuSensor.magXOffset = -50;
  // MpuSensor.magYOffset = -55;
  // MpuSensor.magZOffset = -10;

  delay(3000);
  
  uint8_t sensorId;
  if (MpuSensor.readId(&sensorId) == 0) {
    Serial.println("sensorId: " + String(sensorId));
  } else {
    Serial.println("Cannot read sensorId");
  }  

  Serial.println("Setup ended.");
}

void loop()
{
    static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 500)
    {
        if (MpuSensor.accelUpdate() == 0) {
          aX = MpuSensor.accelX();
          aY = MpuSensor.accelY();
          aZ = MpuSensor.accelZ();
          aSqrt = MpuSensor.accelSqrt();
  
          Serial.print("accel X,Y,Z : ");
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
          Serial.print("  gyro X,Y,Z : ");
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
          Serial.print("  Mag X,Y,Z : ");
          Serial.print(mX);
          Serial.print(" , ");
          Serial.print(mY);
          Serial.print(" , ");
          Serial.print(mZ); 
          Serial.println(" horizontal direction: " + String(mDirection));
        } else {
          Serial.println("Cannot read MAG values");
        }

        prev_ms = millis();
    }
}
