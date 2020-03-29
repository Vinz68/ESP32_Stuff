/* -----------------------------------------------------------------
 * WIFI_KIT_32_VibeSoft is MODIFIED DEMO Code, it original is from:
 * ------------------------------------------------------------------
 * HelTec Automation(TM) WIFI_Kit_32 factory test code 
 * from :  Aaron.Lee from HelTec AutoMation, ChengDu, China
 * original code: https://github.com/HelTecAutomation/Heltec_ESP32
 * 
 * This demo includes follow functions:
 * - Basic OLED function test;
 * - Basic serial port test(in baud rate 115200);
 * - LED blink test;
 * - WIFI join and scan test;
 * ------------------------------------------------------------------
 * 2020-03-29 Additions (VinZ68) 
 * Hardware info:
 *  - Sketch for this ESP32 Development board: https://www.aliexpress.com/item/32842293108.html?spm=a2g0s.9042311.0.0.27424c4dVgt86e
 *  - HiLetgo product page:  https://www.amazon.com/gp/product/B07DKD79Y9/ref=od_aui_detailpages02?ie=UTF8&psc=1
 *  - The OLED is an SSD1306, 128x64 pixels, blue.
 *  Software changes:
 *  - Custom startup logo
 *  - Trim SSIDs ; so info of WIFI access points is more clear
 * ------------------------------------------------------------------
*/

#include "heltec.h"
#include "WiFi.h"
#include "images.h"

void logo()
{
	Heltec.display->clear();
	Heltec.display->drawXbm(0, 0, logo_width, logo_height, (const unsigned char *)logo_bits);
	Heltec.display->drawString(8, 42, "WIFI_Kit_32_VibeSoft");
	Heltec.display->drawString(35, 53, "Version 0.1");
	Heltec.display->display();
}

void WIFISetUp(void)
{
	// Set WiFi to station mode and disconnect from an AP if it was previously connected
	WiFi.disconnect(true);
	delay(1000);
	WiFi.mode(WIFI_STA);
	WiFi.setAutoConnect(true);
	WiFi.begin("WIFI SSID", "Password");
	delay(100);

	byte count = 0;
	while (WiFi.status() != WL_CONNECTED && count < 10)
	{
		count++;
		delay(500);
		Heltec.display->drawString(0, 0, "Connecting...");
		Heltec.display->display();
	}

	Heltec.display->clear();
	if (WiFi.status() == WL_CONNECTED)
	{
		Heltec.display->drawString(0, 0, "Connecting...OK.");
		Heltec.display->display();
	}
	else
	{
		Heltec.display->clear();
		Heltec.display->drawString(0, 0, "Connecting...Failed");
		Heltec.display->display();
		while (1)
			;
	}
	Heltec.display->drawString(0, 10, "WIFI Setup done");
	Heltec.display->display();
	delay(500);
}

void WIFIScan(void)
{
	Heltec.display->drawString(0, 20, "Scan start...");
	Heltec.display->display();

	int n = WiFi.scanNetworks();
	Heltec.display->drawString(0, 30, "Scan done");
	Heltec.display->display();
	delay(500);
	Heltec.display->clear();

	if (n == 0)
	{
		Heltec.display->clear();
		Heltec.display->drawString(0, 0, "no network found");
		Heltec.display->display();
		while (1)
			;
	}
	else
	{
		Heltec.display->drawString(0, 0, (String)n);
		Heltec.display->drawString(14, 0, "networks found:");
		Heltec.display->display();
		delay(500);

		for (int i = 0; i < n; ++i)
		{
			// Print SSID and RSSI for each network found
			Heltec.display->drawString(0, (i + 1) * 9, (String)(i + 1));
			Heltec.display->drawString(6, (i + 1) * 9, ":");

			String maybe2LongSSID = (String)(WiFi.SSID(i));
			int strSize = maybe2LongSSID.length();
			if (strSize > 15)
				maybe2LongSSID.remove(15, strSize - 15);

			Heltec.display->drawString(12, (i + 1) * 9, maybe2LongSSID);
			Heltec.display->drawString(96, (i + 1) * 9, " (");
			Heltec.display->drawString(105, (i + 1) * 9, (String)(WiFi.RSSI(i)));
			Heltec.display->drawString(121, (i + 1) * 9, ") ");
			//            display.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
			delay(10);
		}
	}

	Heltec.display->display();
	delay(800);
	Heltec.display->clear();
}

void setup()
{
	pinMode(LED, OUTPUT);
	digitalWrite(LED, HIGH);

	Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);

	logo();

	delay(5000);
	Heltec.display->clear();

	WIFISetUp();
}

void loop()
{
	WIFIScan();
	delay(2000);
}
