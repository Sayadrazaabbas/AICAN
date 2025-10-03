#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data lines for two sensors
#define ONE_WIRE_BUS1 23
#define ONE_WIRE_BUS2 27

// Create OneWire instances
OneWire oneWire1(ONE_WIRE_BUS1);
OneWire oneWire2(ONE_WIRE_BUS2);

// Pass OneWire references to DallasTemperature
DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("ESP32 + DS18B20 Two Sensors Example");

  sensors1.begin();
  sensors2.begin();
  sensors1.setResolution(12); // 12-bit = 0.0625 °C resolution
  sensors2.setResolution(12);
}

void loop() {
  // Request temperature conversions on both buses
  sensors1.requestTemperatures();
  sensors2.requestTemperatures();

  float tempC1 = sensors1.getTempCByIndex(0); // Sensor on GPIO23
  float tempF1 = sensors1.getTempFByIndex(0);

  float tempC2 = sensors2.getTempCByIndex(0); // Sensor on GPIO27
  float tempF2 = sensors2.getTempFByIndex(0);

  if (tempC1 == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: DS18B20 on GPIO23 not detected!");
  } else {
    Serial.print("Sensor GPIO23: ");
    Serial.print(tempC1, 2);
    Serial.print(" °C  |  ");
    Serial.print(tempF1, 2);
    Serial.println(" °F");
  }

  if (tempC2 == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: DS18B20 on GPIO27 not detected!");
  } else {
    Serial.print("Sensor GPIO27: ");
    Serial.print(tempC2, 2);
    Serial.print(" °C  |  ");
    Serial.print(tempF2, 2);
    Serial.println(" °F");
  }

  delay(1000); // wait 1 second
}