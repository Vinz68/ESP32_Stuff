/*--------------------------------------------------------------------------------------------------------
 * I2C_Scanner_VibeSoft is a scanner that shows the addresses of connected I2C devices. 
 * -------------------------------------------------------------------------------------------------------
 * ESP32 have two I2C busses: I2C0 and I2C1.
 * For the WIFI_KIT_32, the OLED is connected to I2C0, 
 * so if scan with Wire (I2C0), the return address should be 0x3C.
 * 
 * Best practise is to use I2C1 for your connected I2C devices.
 * Note: For I2C1, SDA = GPIO 21 and SCL is GPIO 22.
 * 
 * This demo code:
 * - Scans the 2nd I2C bus (I2C1) and 
 * - Outputs the address of every found device on the OLED 
 * - Outputs the address on the Serial port (Arduino Serial Monitor)
 * 
 * This is a great scanner to see if your attached I2C device is connected properly
 * -------------------------------------------------------------------------------------------------------
*/
#include "Arduino.h"
#include "heltec.h"
#include "images.h"

void logo()
{
	Heltec.display->clear();
	Heltec.display->drawXbm(0, 0, logo_width, logo_height, (const unsigned char *)logo_bits);
	Heltec.display->drawString(8, 42, "I2C_Scanner_VibeSoft");
	Heltec.display->drawString(35, 53, "Version 0.2");
	Heltec.display->display();
}

void setup()
{
	Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
	logo();
	delay(5000);
	Heltec.display->clear();
  
	Wire1.begin(SDA, SCL);   // Scan the device address via I2C1
}


void printInfo(String info, int line)
{
	// Show Info on Serial Monitor
	Serial.println(info);

	// Show Info on OLED display
	Heltec.display->drawString(0, line * 10, info);
	Heltec.display->display();
	delay(500);
}

void loop()
{
	byte error, address;
	int nDevices;
  int line;
  
  Heltec.display->clear();
  String showInfo = "Scanning...";
	printInfo(showInfo, 0);

	nDevices = 0;
  line = 0;
	for(address = 1; address < 127; address++ )
	{
    Wire1.beginTransmission(address);
    error = Wire1.endTransmission();

		if (error == 0)
		{
		  if (nDevices==0)
			{
				Heltec.display->clear();
				showInfo = "I2C device(s) found at: ";
				printInfo(showInfo, 0);
			}

			showInfo = "- address: 0x";
			if (address<16)
				showInfo += "0";
			showInfo += (String(address,HEX));
			nDevices++;
      line++;
			printInfo(showInfo, line);
		}
		else if (error==4)
		{
      showInfo = "Error at address 0x";

      if (address<16)
        showInfo += "0";
      
      showInfo += (String(address,HEX));
      line++;
      printInfo(showInfo, line);      
		}

    if (line>7)
    {
      // Does not fit on OLED, so delay and continue on clear screen.
      delay(4000);
      Heltec.display->clear();
      showInfo = "..continued I2C found at: ";
      printInfo(showInfo, 0);     
      line = 0;  
    }
	}
	if (nDevices == 0)
	{
		showInfo = "No I2C devices found";
		printInfo(showInfo, 1);
	}
	else
	{
		showInfo = "Done";
		printInfo(showInfo, nDevices+1);		
	}

	delay(4000);
}
