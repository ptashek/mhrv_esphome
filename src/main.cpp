#include "DallasTemperature.h"
#include "OneWire.h"

// Sensors are wired to GPIO 0 (D3) on the D1 Wemos Mini
// NOTE: Replace with your GPIO pin
#define ONE_WIRE_BUS 0

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Struct to hold ensor and calibration data
struct sensorConfig {
  DeviceAddress address;
  String name;
  float calibration;
};

// NOTE: Replace the addresses with the addresses of your sensors and calibrate as needed
sensorConfig sensorsConfig[] = {
    {{0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}, "Supply", 0},
    {{0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02}, "Extract", 0},
    {{0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03}, "Intake", 0},
    {{0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04}, "Exhaust", 0}};

void setup() {
  Serial.begin(115200);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();

  // Loop through each device, print out temperature data
  for (int i = 0; i < 4; i++) {
    // Search the one-wire bus for he target sensor address
    if (sensors.getAddress(sensorsConfig[i].address, i)) {
      Serial.print("Temperature for device: ");
      Serial.println(sensorsConfig[i].name);
      // Print the data
      float tempC = sensors.getTempC(sensorsConfig[i].address);
      Serial.print("Temp C: ");
      Serial.println(tempC);
    }
  }

  Serial.println("--------------------");
  delay(5000);
}