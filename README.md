BLE-Weather-monitor-
Using ESP32 Tempeture and humidity value sending through BLE using Nordic Application

Table of Contents
- [Introduction](#introduction)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Code Explanation](#code-explanation)
Introduction

This project uses the ESP32 microcontroller and the DFRobot DHT11 sensor to measure temperature and humidity. The data is then transmitted over Bluetooth Low Energy (BLE) to a connected device.

Hardware Requirements

- ESP32 Development Board
- DHT11 Temperature and Humidity Sensor
- Hardware sketch or Demo not available in this repository rite now if required let me know

Software Requirements

- Arduino IDE
- ESP32 Board Package
- Libraries:
  - `BLEDevice.h`
  - `BLEServer.h`
  - `BLEUtils.h`
  - `BLE2902.h`
  - `DFRobot_DHT11.h`
 
The Service UUID and Cheracterstics UUID  same as given doc

Installation

1. Install the ESP32 board package in Arduino IDE. Follow the instructions (https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md).
2. Install the required libraries:
   - Open Arduino IDE.
   - Go to `Sketch` -> `Include Library` -> `Manage Libraries`.
   - Search for `ESP32 BLE Arduino` and install it.
   - Search for `DFRobot DHT11` and install it.
3. Clone this repository or download the ZIP file and extract it.
4. Open the `weather_station.ino` file in Arduino IDE.

Usage

1. Connect the DHT11 sensor to the ESP32:
   - VCC to 3.3V
   - GND to GND
   - Data to GPIO 17 (DHT11_PIN)
2. Upload the code to the ESP32.
3. Open the Serial Monitor to see the temperature and humidity readings.
4. Use  nRF Connect app to connect to the ESP32 and read the characteristics.

 Code Explanation

The code initializes the BLE device, sets up the server, service, and characteristics, and reads data from the DHT11 sensor to send it over BLE.

Libraries

- `BLEDevice.h`, `BLEServer.h`, `BLEUtils.h`, `BLE2902.h`: These libraries are used to handle BLE communication.
- `DFRobot_DHT11.h`: This library is used to interface with the DHT11 sensor.

BLE Setup

The `initBLE` function initializes the BLE device and sets up the server, service, and characteristics. It also starts advertising the BLE service.

Reading Sensor Data

The `loop` function reads the temperature and humidity data from the DHT11 sensor every second. If a BLE device is connected, it sends the data as notifications.

```cpp
void loop(){
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
  delay(1000);

  if (deviceConnected){
    DHT.read(DHT11_PIN);
    Tempeture.setValue(DHT.temperature);
    Tempeture.notify();
    Humidity.setValue(DHT.humidity);
    Humidity.notify();
  }
}
