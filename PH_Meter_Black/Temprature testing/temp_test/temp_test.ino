#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;  // ADS1115 object

// --- Thermistor constants ---
const float SERIES_RESISTOR = 10000.0;   // Divider resistor value (10k)
const float NOMINAL_RESISTANCE = 10000.0; // NTC resistance at 25°C
const float NOMINAL_TEMPERATURE = 25.0;   // 25°C reference
const float B_COEFFICIENT = 3950.0;       // Beta value from datasheet

// --- ADS1115 parameters ---
const float ADC_GAIN = 0.1875F; // ADS1115 gain (mV/bit at GAIN_TWOTHIRDS)

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS1115!");
    while (1);
  }

  // Set gain = ±6.144V (default)
  ads.setGain(GAIN_TWOTHIRDS);
}

void loop() {
  // Read single-ended input A0 (thermistor divider output)
  int16_t adc0 = ads.readADC_SingleEnded(0);

  // Convert ADC reading to voltage
  float voltage = adc0 * ADC_GAIN / 1000.0; // in Volts (ADS1115 step is in mV)
  
  // Assuming divider: NTC between GND and A0, fixed resistor to VCC
  float vcc = 3.3;  // System voltage (use 5.0 if using 5V divider)
  float resistance = SERIES_RESISTOR * (vcc / voltage - 1.0);

  // Steinhart–Hart equation (simplified)
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;      // (R/Ro)
  steinhart = log(steinhart);                       // ln(R/Ro)
  steinhart /= B_COEFFICIENT;                       // 1/B * ln(R/Ro)
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);// + (1/To)
  steinhart = 1.0 / steinhart;                      // Invert
  steinhart -= 273.15;                              // Convert to °C

  Serial.print("ADC Reading: "); Serial.print(adc0);
  Serial.print("  Voltage: "); Serial.print(voltage, 3); Serial.print(" V");
  Serial.print("  Resistance: "); Serial.print(resistance, 1); Serial.print(" ohms");
  Serial.print("  Temp: "); Serial.print(steinhart, 2); Serial.println(" °C");

  delay(1000);
}
