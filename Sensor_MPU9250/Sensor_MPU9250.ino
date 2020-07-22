#include "heltec.h"
#include "WiFi.h"
#include "images.h"
#include <MPU9250_asukiaaa.h>

#define SDA_PIN 21
#define SCL_PIN 22

MPU9250_asukiaaa MpuSensor;
float aX, aY, aZ, aSqrt;
float gX, gY, gZ;

void logo(){
  Heltec.display -> clear();
  Heltec.display -> drawXbm(0,0,logo_width,logo_height,(const unsigned char *)logo_bits);
  Heltec.display -> drawString( 8, 42, "MPU9250_VibeSoft"); 
  Heltec.display -> drawString(35, 53, "Version 0.2");   
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

  delay(5000);
  Heltec.display->clear();

  Serial.println("MPU9250 Setup...");
  MpuSensor.setWire(&Wire);  
  MpuSensor.beginAccel();
  MpuSensor.beginGyro();

  Serial.println("Setup ended.");
}

void loop()
{
    static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 20)
    {
        MpuSensor.accelUpdate();
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

        MpuSensor.gyroUpdate();
        gX = MpuSensor.gyroX();
        gY = MpuSensor.gyroY();
        gZ = MpuSensor.gyroZ();
        Serial.print("  gyro X,Y,Z : ");
        Serial.print(gX);
        Serial.print(" , ");
        Serial.print(gY);
        Serial.print(" , ");
        Serial.println(gZ);        

        prev_ms = millis();
    }
}
