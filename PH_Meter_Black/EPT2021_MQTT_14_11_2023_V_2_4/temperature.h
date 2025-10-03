////#include <OneWire.h>
////#include <DallasTemperature.h>
////
////
////#define ONE_WIRE_BUS 19             // DS18b20 Sensor
////#define TEMPERATURE_PRECISION 12    // DS18b20 Temperature Precision
////
////
////OneWire oneWire(ONE_WIRE_BUS);
////DallasTemperature sensors(&oneWire);
////// Hold device address
////DeviceAddress Thermometer;
//
//
///// temperature sensor call and updation
////float room_temp(){
////  sensors.begin();
////  sensors.requestTemperatures(); // Send the command to get updated temperatures
////  vals = sensors.getTempCByIndex(0);
////  if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/TEMP_VAL", vals);
////  return vals;
////  }
//
//
//
//
////
////float room_temp(){
////  float Vi = analogRead(34) * (3.3 / 4095.0);
////  //Convert voltage measured to resistance value
////  //All Resistance are in kilo ohms.
////  float R = (Vi * Rseries) / (3.3 - Vi);
////  /*Use R value in steinhart and hart equation
////    Calculate temperature value in kelvin*/
////  float T =  1 / ((1 / To) + ((log(R / Ro)) / B));
////  vals = T - 273.15 -12; // Converting kelvin to celsius
////  if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/TEMP_VAL", vals);
////  return vals;
//////  
////}
//
////const double VCC = 3.3;             // NodeMCU on board 3.3v vcc
////const double R2 = 47000;            // 10k ohm series resistor
////const double adc_resolution = 4095; // 10-bit adc
////
////const double A = 0.001129148;   // thermistor equation parameters
////const double B = 0.000234125;
////const double C = 0.0000000876741; 
////
//
////float room_temp(){
////  double Vout, Rth, temperature, adc_value; 
////
////  adc_value = analogRead(34);
////  Vout = (adc_value * VCC) / adc_resolution;
////  Rth = (VCC * R2 / Vout) - R2;
//
///*  Steinhart-Hart Thermistor Equation:
// *  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)
//// *  where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
////  temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)),3))));   // Temperature in kelvin
////
////  vals = temperature - 273.15;  // Temperature in degree celsius
////  if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/TEMP_VAL", vals);
////  return vals;
////}
