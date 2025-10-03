#include<ADS1115_lite.h>
ADS1115_lite adc(ADS1115_DEFAULT_ADDRESS);

int B =  3950; //Nominal resistance 50K, Beta constant
int Rseries = 4.7;// Series resistor 10K
float To = 298.15; // Nominal Temperature



void ads_config() {
  adc.setGain(ADS1115_REG_CONFIG_PGA_4_096V);
  adc.setSampleRate(ADS1115_REG_CONFIG_DR_860SPS);
}

int16_t ads_read() {
  adc.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_0);  // Single mode input on AIN0 (AIN0 - GND)
  adc.triggerConversion();  // Triggered mannually
  return adc.getConversion();  // returns int16_t value
}

int16_t ads_read_temp() {
  adc.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_1);  // Single mode input on AIN0 (AIN0 - GND)
  adc.triggerConversion();  // Triggered mannually
  return adc.getConversion();  // returns int16_t value
}
int16_t ads_read_battery() {
  adc.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_2);  // Single mode input on AIN0 (AIN0 - GND)
  adc.triggerConversion();  // Triggered mannually
  return adc.getConversion();  // returns int16_t value
}
//float room_temp() {
//  double Vout, Rth, temperature, adc_value;  // PTC FUNCTION
//  adc_value = ads_read_temp();
//  Serial.print(" degree celsius  : ");
//  Serial.println(adc_value);
//  Vout = (adc_value * VCC) / adc_resolution;
//  Rth = (VCC * R2 / Vout) - R2;
//  /*  Steinhart-Hart Thermistor Equation:
//      Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)
//      where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
//      temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)), 3))));  // Temperature in kelvin
//
//  vals = temperature - 273.15 + R_C;  // Temperature in degree celsius
//  Serial.println(" degree celsius");
//  Serial.println(vals);
//  if (WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2006/Data/TEMP_VAL", vals);
//  else data_sender("TEMP_VAL", String(vals));
//  return vals;
//  //
//}

//float room_temp() {
//  int raw = ads_read_temp();  //NTC function
////  Serial.println("  ");
////  Serial.println("###########################################");
//  Serial.print("rawadcfortemp: = ");
//  Serial.println(raw);
//
//  float Vi =  raw * 0.125 / 1000;
//  Serial.print("Vi  = ");
//  Serial.println(Vi);
//  //Convert voltage measured to resistance value
//  //All Resistance are in kilo ohms.
//  float R = (Vi * Rseries) / (3.3 - Vi);
//  Serial.print("R_C = ");
//  Serial.println(R_C);
//  /*Use R value in steinhart and hart equation
//    Calculate temperature value in kelvin*/
//  float T =  1 / ((1 / To) + ((log(R / 9.12)) / BN));
//  Serial.print("T = ");
//  Serial.println(T);
//  vals = T - 273.15 + R_C; // Converting kelvin to celsius
//  data_sender("TEMP_VAL", String(vals));
//  Serial.print("Vals = ");
//  Serial.println(vals);
//  return vals;
//}
float room_temp() {
  int raw = ads_read_temp();
  data_sender("A1", String(raw));
  Serial.print("                                                   rawadcfortemp:");
  Serial.println(raw);
  float Vi =  raw * 0.125 / 1000;
  Serial.print(" Vi: ");
  Serial.println(Vi);
  //Convert voltage measured to resistance value
  //All Resistance are in kilo ohms.
  float R = (Vi * Rseries) / (5.0 - Vi);
  Serial.print(" R: ");
  Serial.println(R);
  if (R <= 1)R = 4.8;
  Serial.print(" AFTER_R: ");
  Serial.println(R);
  /*Use R value in steinhart and hart equation
    Calculate temperature value in kelvin*/
  float T =  1 / ((1 / To) + ((log(R / 9.12)) / B));
  Serial.print(" T:");
  Serial.println(T);
  temp_vals = T - 273.15/* + Ro */+ R_C - 12; // Converting kelvin to celsius
  Serial.print(" temp_vals: ");
  Serial.println(temp_vals);
  total = total - readings[readIndex];
  readings[readIndex] = temp_vals;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
  vals = average;
  Serial.print("vals: ");
  Serial.println(vals);
//  if (vals < 15)vals = vals - 6;
  //  if (vals > 31)vals = vals + 4;
//  if (vals < 1)vals = 0;

  String runningdisp;
  jsonDoc["temp_vals"] = vals;
  float main_val = ads_read();
  data_sender("A0", String(main_val));
  serializeJson(jsonDoc, runningdisp);
  Serial2.println(runningdisp);
  //  data_sender("TEMP_VAL", String(vals));
  data_sender("TEMP_VAL", String(vals));
  return vals;
}
