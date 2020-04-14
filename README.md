# ESP32_Stuff
ESP32 code for my ESP32 Development board, using Arduino IDE. See table below.


## [The hardware](https://www.aliexpress.com/item/32842293108.html?spm=a2g0s.9042311.0.0.27424c4dVgt86e)
ESP32 Development board called *["WiFi Kit 32"](https://heltec.org/project/wifi-kit-32/)* Developer board from Heltec Automation with:
- Tensilica LX6 dual-core processor, clocked at 240MHz, computing power up to 600DMIPS,
- Chip built-in 520 KB SRAM and Onboard 32MByte Flash
- Bluetooth: integrated dual-mode Bluetooth (traditional Bluetooth and BLE low power Bluetooth)
- Wifi: transceiver 802.11 b/g/N HT40（not include Antenna）
- SX1278 chip for LoRa remote modem, 433MHz frequency (measured open area communication distance 2.6Km).
- Onboard 0.96 Inch OLED Display with 128x64 pixels, Blue, SSD1306 chipset/driver
- lithium battery (lipo) charging circuit and interface
- CP2102 Module USB to serial chip 


![](https://raw.githubusercontent.com/Vinz68/ESP32_Stuff/master/resources/WiFi_Kit_32.png "WIFI KIT 32 Developer Board")


## [The Code]()

| Code                    | Description                                   | Pins used        |
| ----------------------- | --------------------------------------------- | ----------------:|
| I2C_Scanner_VibeSoft    | Scans for I2C devices on 2nd I2C bus          | SDA on GPIO 21   |
|                         | Output on OLED display and serial port.       | SCL on GPIO 22   |
|  |  | 
| Sensor_MPU6050          | Gyro Sensor, read X,Y and Z angles            | SDA on GPIO 21   |
|  || SCL on GPIO 22   | 
|  || INT on GPIO 2   | 
|  |  |
| WIFI_KIT_32_VibeSoft    | Wifi scanner with minor modifications         | *not applicable* |
|  |  |
|  |  | 

## [The documentation](https://www.amazon.com/gp/product/B07DKD79Y9/ref=od_aui_detailpages02?ie=UTF8&psc=1)
Additional documentation, used in the source code
- [681 pages manual - ESP32](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [Heltec files, install guide and bunches of info](https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series)
- [OLED SSD1306 Driver Library - u8g2](https://github.com/olikraus/u8g2)


I2C Scanner at work with a I2C Gyro sensor (MPU-6050)
![I2C Scanner with a I2C Gyro sensor (MPU-6050](https://raw.githubusercontent.com/Vinz68/ESP32_Stuff/master/resources/I2C_Scanner.png "I2C Scanner with a I2C Gyro sensor (MPU-6050)")


