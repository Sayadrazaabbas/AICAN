#include<ADS1115_lite.h>
ADS1115_lite adc(ADS1115_DEFAULT_ADDRESS);

int B =  3950; //Nominal resistance 50K, Beta constant
int Rseries = 4.7;// Series resistor 10K
float To = 298.15; // Nominal Temperature

void ads_config() {
  adc.setGain(ADS1115_REG_CONFIG_PGA_4_096V);
  adc.setSampleRate(ADS1115_REG_CONFIG_DR_860SPS);
  Serial.print("Configuring Ads");
}

int16_t ads_read() {
  adc.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_0);  // Single mode input on AIN0 (AIN0 - GND)
  adc.triggerConversion();  // Triggered mannually
  return adc.getConversion();  // returns int16_t value
}

int16_t ads_read_temp() {
  adc.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_1);  // Single mode input on AIN0 (AIN0 - GND)
  adc.triggerConversion();     //Triggered mannually
  return adc.getConversion();  //returns int16_t value
}

int16_t ads_read_bat() {
  adc.setMux(ADS1115_REG_CONFIG_MUX_SINGLE_2);  // Single mode input on AIN0 (AIN0 - GND)
  adc.triggerConversion();  // Triggered mannually
  return adc.getConversion();  // returns int16_t value
}

float room_temp() {
  int raw = ads_read_temp();
  Serial.print("rawadcfortemp:-");
  Serial.println(raw);
  float Vi =  raw * 0.125 / 1000;
  //Convert voltage measured to resistance value
  //All Resistance are in kilo ohms.
  float R = (Vi * Rseries) / (3.3 - Vi);
  /*Use R value in steinhart and hart equation
    Calculate temperature value in kelvin*/
  float T =  1 / ((1 / To) + ((log(R / 9.12)) / B));

  vals = T - 273.15 + Ro; // Converting kelvin to celsius
//  if (WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/TEMP_VAL", vals);
  if (currentMillis - lastTempPublish >= PUBLISH_INTERVAL) {
    snprintf(Temp_val,sizeof(Temp_val),"%f",vals);
    client.publish(TEMP_VAL.c_str(), Temp_val);
    lastTempPublish = currentMillis;  // Update the last publish time
  }
//  client.publish(TEMP_VAL,Temp_val);
  return vals;
}
