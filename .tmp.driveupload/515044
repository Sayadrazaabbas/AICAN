float pH;
int lastUpload = 0;
float volt;
float uni_volt;
void phCalRoutine(void);
int cf = 0;
float ps;
float p1;
int val;

//function declaration
float compen_pH(float entered_Val0, int y);

float mV_calc(float voltage) {
  float y;
  if (voltage < 0.53) y = -254.2857 * voltage + 489.7714;
  if (voltage > 0.53 && voltage < 1.23) y = -254.2857 * voltage + 489.7714;
  if (voltage > 1.23 && voltage < 1.93) y = -252.8571 * voltage + 488.0143;
  if (voltage > 1.93 && voltage < 2.57) y = -276.5625 * voltage + 533.7656;
  if (voltage > 2.57 && voltage < 3.19) y = -233.871 * voltage + 424.0484;
  if (voltage > 3.19) y = -233.871 * voltage + 424.0484;
  return y;

}
// final output pH algorithm
float readpH() {

  float buffer_arr[100];

  float temp, avgval, calibration_value, ph_n;

  // Averaging Algorithm
  for (int i = 0; i < 100; i++)
  {
    buffer_arr[i] = ads_read();
    (100);
  }
  for (int i = 0; i < 100; i++)
  {
    for (int j = i + 1; j < 100; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 0; i < 100; i++)
  {
    avgval += buffer_arr[i];
  }
  volt = (float)avgval * 0.125 / 1000 / 100;
  // Serial.print("Voltage:       ");
  // Serial.println(volt);
  // Stabilization Algorithm
  if (cf > 0) {
    p1 = pH;
  }
  else {
    p1 = 0;
  }
  cf++;
  if (atc_var == 0) {
    if (cal_mode == 2) {
      Serial.println("                  voltage  = " + String(volt));
      Serial.println("phCalValue3                  phCalCoeff3 ");
      Serial.println(String(phCalValue[0]) + "                            " + String(phCalCoeff[0]));
      Serial.println(String(phCalValue[1]) + "                            " + String(phCalCoeff[1]));
      Serial.println(String(phCalValue[2]) + "                            " + String(phCalCoeff[2]));
      Serial.println(String(phCalValue[3]) + "                            " + String(phCalCoeff[3]));
      Serial.println(String(phCalValue[4]) + "                            " + String(phCalCoeff[4]));

      if (volt < phCalValue[0]) ph_n = phCalCoeff[0] * volt + phCalCoeff[1];
      if (volt > phCalValue[0] && volt < phCalValue[1]) ph_n = phCalCoeff[0] * volt + phCalCoeff[1];
      if (volt > phCalValue[1] && volt < phCalValue[2]) ph_n = phCalCoeff[2] * volt + phCalCoeff[3];
      if (volt > phCalValue[2] && volt < phCalValue[3]) ph_n = phCalCoeff[4] * volt + phCalCoeff[5];
      if (volt > phCalValue[3] && volt < phCalValue[4]) ph_n = phCalCoeff[6] * volt + phCalCoeff[7];
      if (volt > phCalValue[4]) ph_n = phCalCoeff[6] * volt + phCalCoeff[7];
    }
    else if (cal_mode == 1) {
      //      phCalCoeff3[3] = 0.14;
      Serial.println("                  voltage  = " + String(volt));
      Serial.println("phCalValue3                  phCalCoeff3 ");
      Serial.println(String(phCalValue3[0]) + "                            " + String(phCalCoeff3[0]));
      Serial.println(String(phCalValue3[1]) + "                            " + String(phCalCoeff3[1]));
      Serial.println(String(phCalValue3[2]) + "                            " + String(phCalCoeff3[2]));
      Serial.println(/*String(phCalValue3[3]) + */"                                                        " + String(phCalCoeff3[3]));

      if (volt < phCalValue3[0]) {
        Serial.println(" LINE 1");
        ph_n = phCalCoeff3[0] * volt + phCalCoeff3[1];
      }
      if (volt > phCalValue3[0] && volt < phCalValue3[1]) {
        ph_n = phCalCoeff3[0] * volt + phCalCoeff3[1];
        Serial.println(" LINE 2");
      }
      if (volt > phCalValue3[1] && volt < phCalValue3[2]) {
        ph_n = phCalCoeff3[2] * volt + phCalCoeff3[3];
        Serial.println(" LINE 3");
      }
      if (volt > phCalValue3[2]) {
        ph_n = phCalCoeff3[2] * volt + phCalCoeff3[3];
        Serial.println(" LINE 4");
      }
    }
  }
  data_sender("VOLTAGE", String(volt));
  ps = ph_n;
  float p2 = ph_n;

  if (p2 > p1 + 0.02 || p2 < p1 - 0.02) {
    pH = p2;
  }

  else pH = p1;
  uni_volt = volt;
  Serial.println("readPH function:");
  Serial.print("ph_n = ");
  Serial.println(ph_n);
  Serial.print("pH");
  Serial.println(pH);
  return pH;
}








float readCalpH() {
  float buffer_arr[35];
  float temp, avgval, calibration_value;

  // Averaging Algorithm
  for (int i = 0; i < 35; i++)
  {
    buffer_arr[i] = ads_read();
    (100);
  }
  for (int i = 0; i < 35; i++)
  {
    for (int j = i + 1; j < 35; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 0; i < 35; i++)
  {
    avgval += buffer_arr[i];
  }
  float volt = (float)avgval * 0.125 / 1000 / 35;
  //volt = floor(100000*volt)/100000;
  Serial.print("Voltage: ");
  Serial.println(volt, 4);
  return volt;
}













//****************************************************************    Calibration Routine  *********************************************************************
//****************************************************************    Calibration Routine  *********************************************************************
//****************************************************************    Calibration Routine  *********************************************************************

void phCalRoutine() {
  if (millis() - lastUpload >= 5000)
  {
    if (calButton == 50) {
      Serial.print("i am in 50");
      cal_disp(bufferValue[4]);
      float v5 = readCalpH();
      float b5 = bufferValue[4];
      c5 = compen_pH(b5, 4);
      data_sender("VAL_5", String(v5));
      float x5 =  59.16 * c5 - 414.12;
      data_sender("MV_5", String(x5));
      phCalValue[4] = v5;
      write_phcal_EEPROM();
    }
    else if (calButton == 10) {
      Serial.println("i am in 10");
      cal_disp(bufferValue[0]);
      float v1 = readCalpH();
      float b1 = bufferValue[0];
      c1 = compen_pH(b1, 0);
      float x1 = 59.16 * c1 - 414.12;
      data_sender("VAL_1", String(v1));
      data_sender("MV_1", String(x1));
      phCalValue[0] = v1;
      write_phcal_EEPROM();
    }
    else if (calButton == 20) {
      Serial.print("i am in 20");
      if (cal_mode == 1) {
        cal_disp(bufferValue3[0]);
        float v2 = readCalpH();
        float b2 = bufferValue3[0];
        c2 = compen_pH(b2, 0);
        Serial.println("C2 = ");
        Serial.println(c2);
        data_sender("VAL_2", String(v2));
        float x2 = 59.16 * c2 - 414.12;
        data_sender("MV_2", String(x2));
        phCalValue3[0] = v2;
        Serial.print("V2 = ");
        Serial.println(v2);
        Serial.print("phCalValue3[0]  V2 = ");
        Serial.println(phCalValue3[0]);
      }
      else if (cal_mode == 2) {
        cal_disp(bufferValue[1]);
        float v2 = readCalpH();
        float b2 = bufferValue[1];
        c2 = compen_pH(b2, 1);
        data_sender("VAL_2", String(v2));
        float x2 = 59.16 * c2 - 414.12;
        data_sender("MV_2", String(x2));
        phCalValue[1] = v2;
      }
      write_phcal_EEPROM();
    }
    else if (calButton == 30) {
      Serial.print("i am in 30");
      if (cal_mode == 1) {
        cal_disp(bufferValue3[1]);
        float v3 = readCalpH();
        float b3 = bufferValue3[1];
        c3 = compen_pH(b3, 1);
        Serial.println("C3 = ");
        Serial.println(c3);
        data_sender("VAL_3", String(v3));
        float x3 =  59.16 * c3 - 414.12;
        data_sender("MV_3", String(x3));
        phCalValue3[1] = v3;
        Serial.print("V3 = ");
        Serial.println(v3);
        Serial.print("phCalValue3[1]  V3 = ");
        Serial.println(phCalValue3[1]);

      } else if (cal_mode == 2) {
        cal_disp(bufferValue[2]);
        float v3 = readCalpH();
        float b3 = bufferValue[2];
        c3 = compen_pH(b3, 2);
        data_sender("VAL_3", String(v3));
        float x3 =  59.16 * c3 - 414.12;
        data_sender("MV_3", String(x3));
        phCalValue[2] = v3;
      }
      write_phcal_EEPROM();
    }
    else if (calButton == 40) {
      Serial.print("i am in 40");
      if (cal_mode == 1) {
        cal_disp(bufferValue3[2]);
        float v4 = readCalpH();
        float b4 = bufferValue3[2];
        c4 = compen_pH(b4, 2);
        Serial.println("C4 = ");
        Serial.println(c4);
        data_sender("VAL_4", String(v4));
        float x4 =  59.16 * c4 - 414.12;
        data_sender("MV_4", String(x4));
        phCalValue3[2] = v4;


        Serial.print("V4 = ");
        Serial.println(v4);
        Serial.print("phCalValue3[2]  V4 = ");
        Serial.println(phCalValue3[2]);
      }
      else if (cal_mode == 2) {
        cal_disp(bufferValue[3]);
        float v4 = readCalpH();
        float b4 = bufferValue[3];
        c4 = compen_pH(b4, 3);
        data_sender("VAL_4", String(v4));
        float x4 =  59.16 * c4 - 414.12;
        data_sender("MV_4", String(x4));
        phCalValue[3] = v4;
      }
      write_phcal_EEPROM();
    }
    lastUpload = millis();
  }
}
//****************************************************************    Calibration Routine  *********************************************************************
//****************************************************************    Calibration Routine  *********************************************************************
//****************************************************************    Calibration Routine  *********************************************************************


































//***************************************************************************************    EQUATION SELECTION FUNCTION ***********************************************************************************
//***************************************************************************************    EQUATION SELECTION FUNCTION ***********************************************************************************
//***************************************************************************************    EQUATION SELECTION FUNCTION ***********************************************************************************

// For these 7 Equations X is temperature and Y is pH
// Equation for 1.68pH
float eqn1(float x) {
  float y = 1.668489 + 0.0001743257 * x + 0.00001348651 * x * x;
  return y;
}

// Equation for 4.01pH
float eqn2(float x) {
  float y = 4.01228 - 0.001523976 * x + 0.00004945055 * x * x ;
  return y;
}

// Equation for 6.86pH
float eqn3(float x) {
  float y = 6.978434 - 0.006216284 * x + 0.00006483516 * x * x;
  return y;
}

// Equation for 7.00pH
float eqn4(float x) {
  float y = 7.120302 - 0.006543956 * x + 0.00007002997 * x * x;
  return y;
}

// Equation for 9.18pH
float eqn5(float x) {
  float y = 9.45283 - 0.01321928 * x + 0.00008841159 * x * x ;
  return y;
}

// Equation for 10.01pH
float eqn6(float x) {
  float y = 10.31904 - 0.01473776 * x + 0.0001 * x * x ;
  return y;
}

// Equation for 12.46pH
float eqn7(float x) {
  float y = 13.46923 - 0.04578322 * x + 0.0002195804 * x * x ;
  return y;
}


float compen_pH(float entered_Val0, int y) {
  float est_pH;

  if (entered_Val0 <= 4.01 && entered_Val0 > 1.68) {
    float Val1 = eqn1(manual_atc);
    float Val2 = eqn2(manual_atc);

    float offVal1 = abs(Val1 - 1.68);
    float offVal2 = abs(Val2 - 4.01);

    float finalOff = offVal1 + offVal2 ;
    finalOff = finalOff / 2 ;

    if (manual_atc < 25) entered_Val0 = entered_Val0 - finalOff;
    else entered_Val0 = entered_Val0 + finalOff;
  }

  else if (entered_Val0 <= 6.86 && entered_Val0 > 4.01) {

    float Val1 = eqn2(manual_atc);
    float Val2 = eqn3(manual_atc);

    float offVal1 = abs(Val1 - 4.01);
    float offVal2 = abs(Val2 - 6.86);

    float finalOff = offVal1 + offVal2 ;
    finalOff = finalOff / 2 ;

    if (manual_atc < 25) entered_Val0 = entered_Val0 - finalOff;
    else entered_Val0 = entered_Val0 + finalOff;
  }

  else if (entered_Val0 <= 7 && entered_Val0 > 6.86) {

    float Val1 = eqn3(manual_atc);
    float Val2 = eqn4(manual_atc);

    float offVal1 = abs(Val1 - 6.86);
    float offVal2 = abs(Val2 - 7.00);

    float finalOff = offVal1 + offVal2 ;
    finalOff = finalOff / 2 ;

    if (manual_atc < 25) entered_Val0 = entered_Val0 + finalOff;
    else entered_Val0 = entered_Val0 - finalOff;
  }

  else if (entered_Val0 <= 9.18 && entered_Val0 > 7) {

    float Val1 = eqn4(manual_atc);
    float Val2 = eqn5(manual_atc);

    float offVal1 = abs(Val1 - 7);
    float offVal2 = abs(Val2 - 9.18);

    float finalOff = offVal1 + offVal2 ;
    finalOff = finalOff / 2 ;

    if (manual_atc < 25) entered_Val0 = entered_Val0 + finalOff;
    else entered_Val0 = entered_Val0 - finalOff;
  }

  else  if (entered_Val0 <= 10.01 && entered_Val0 > 9.18) {

    float Val1 = eqn5(manual_atc);
    float Val2 = eqn6(manual_atc);

    float offVal1 = abs(Val1 - 9.18);
    float offVal2 = abs(Val2 - 10.01);

    float finalOff = offVal1 + offVal2 ;
    finalOff = finalOff / 2 ;

    if (manual_atc < 25) entered_Val0 = entered_Val0 + finalOff;
    else entered_Val0 = entered_Val0 - finalOff;
  }

  else if (entered_Val0 <= 12.46 && entered_Val0 > 10.01) {

    float Val1 = eqn6(manual_atc);
    float Val2 = eqn7(manual_atc);

    float offVal1 = abs(Val1 - 10.01);
    float offVal2 = abs(12.46 - Val2);

    float finalOff = offVal1 + offVal2 ;
    finalOff = finalOff / 2 ;

    if (manual_atc < 25) entered_Val0 = entered_Val0 + finalOff;
    else entered_Val0 = entered_Val0 - finalOff;

  }
  else if (cal_mode == 1 ) {
    entered_Val0 = bufferValue3[y];
  }
  else if (cal_mode == 2 ) {
    entered_Val0 = bufferValue[y];
  }
  est_pH = entered_Val0;
  return est_pH;
}
//***************************************************************************************    EQUATION SELECTION FUNCTION ***********************************************************************************
//***************************************************************************************    EQUATION SELECTION FUNCTION ***********************************************************************************
//***************************************************************************************    EQUATION SELECTION FUNCTION ***********************************************************************************




























//***************************************************************************************    ATC _ FUNCTION ***********************************************************************************
//***************************************************************************************    ATC _ FUNCTION ***********************************************************************************
//***************************************************************************************    ATC _ FUNCTION ***********************************************************************************


//
////Automatic Temperature Compensation
//float atc_fn() {
//  float PHVal, temperature_t, finalOffset, calib_temp;
//  calib_temp = 25.00;
//
//  PHVal = readpH();
//  temperature_t = room_temp();
//  //temperature_t = 32;
//  if (PHVal > 0 && PHVal <= 1.68) {
//    return PHVal;
//  }
//
//  else if (PHVal > 1.68 && PHVal <= 4.01) {
//    //    Serial.println("Enter 2");
//    // PH Value is between 1.68 to 4.01 Call equation function 1 & 2
//    float Val1 = eqn1(temperature_t);     // Uncalibrated ATC pH value in Val1
//    float Val2 = eqn2(temperature_t);     // Uncalibrated ATC pH value in Val2
//
//    float offVal1 = abs(Val1 - 1.68);        // Get Offset for this Eqn w.r.t. standard value
//    float offVal2 = abs(4.01 - Val2);        // Get Offset for this Eqn w.r.t. standard value
//
//    finalOffset = offVal1 + offVal2 ;
//    finalOffset = finalOffset / 2 ;
//    Serial.print("finalOffset:      ");
//    Serial.println(finalOffset);
//    // If temperature greater than 25(Calibrated set Temperature) then Subtract final offset from PHVal Else Add offset to it.
//    if (temperature_t > calib_temp) {
//      PHVal = PHVal + finalOffset;
//      //      Serial.print("ATC pH:");
//      //      Serial.print(PHVal);
//      return PHVal;
//    }
//    else {
//      PHVal = PHVal - finalOffset;
//      //      Serial.print("ATC pH:");
//      //      Serial.print(PHVal);
//      return PHVal;
//    }
//  }
//
//  else if (PHVal > 4.01 && PHVal <= 6.86) {
//    //Serial.println("Enter 3");
//    // PH Value is between 4.01 to 6.86 Call equation function 2 & 3
//    float Val1 = eqn2(temperature_t);
//    float Val2 = eqn3(temperature_t);
//
//    float offVal1 = abs(Val1 - 4.01);        // Get Offset for this Eqn w.r.t. standard value
//    float offVal2 = abs(6.86 - Val2);        // Get Offset for this Eqn w.r.t. standard value
//
//    finalOffset = offVal1 + offVal2 ;
//    finalOffset = finalOffset / 2 ;
//    Serial.print("finalOffset:      ");
//    Serial.println(finalOffset);
//    // If temperature greater than 25(Calibrated set Temperature) then Subtract final offset from PHVal Else Add offset to it.
//    if (temperature_t > calib_temp) {
//      PHVal = PHVal + finalOffset;
//      return PHVal;
//    } else {
//      PHVal = PHVal - finalOffset;
//      return PHVal;
//    }
//  }
//
//  else if (PHVal > 6.86 && PHVal <= 9.18) {
//    //Serial.println("Enter 4");
//    // PH Value is between 6.86 to 7.00 Call equation function 3 & 4
//    float Val1 = eqn3(temperature_t);
//    float Val2 = eqn5(temperature_t);
//
//    float offVal1 = abs(Val1 - 6.86);        // Get Offset for this Eqn w.r.t. standard value
//    float offVal2 = abs(9.18 - Val2);        // Get Offset for this Eqn w.r.t. standard value
//
//    finalOffset = offVal1 + offVal2 ;
//    finalOffset = finalOffset / 2 ;
//    Serial.print("finalOffset:       ");
//    Serial.println(finalOffset);
//    // If temperature greater than 25(Calibrated set Temperature) then Subtract final offset from PHVal Else Add offset to it.
//    if (temperature_t > calib_temp) {
//      PHVal = PHVal + finalOffset;
//      return PHVal;
//    } else {
//      PHVal = PHVal - finalOffset;
//      return PHVal;
//    }
//  }
//
//  else if (PHVal > 9.18 && PHVal <= 10.01) {
//    //Serial.println("Enter 6");
//    // PH Value is between 9.18 to 10.01 Call equation function 5 & 6
//    float Val1 = eqn5(temperature_t);
//    float Val2 = eqn6(temperature_t);
//
//    float offVal1 = abs(Val1 - 9.18);        // Get Offset for this Eqn w.r.t. standard value
//    float offVal2 = abs(10.01 - Val2);        // Get Offset for this Eqn w.r.t. standard value
//    finalOffset = offVal1 + offVal2 ;
//    finalOffset = finalOffset / 2 ;
//    Serial.print("finalOffset:   ");
//    Serial.println(finalOffset);
//    // If temperature greater than 25(Calibrated set Temperature) then Subtract final offset from PHVal Else Add offset to it.
//    if (temperature_t > calib_temp) {
//      PHVal = PHVal + finalOffset;
//
//      return PHVal;
//    } else {
//      PHVal = PHVal - finalOffset;
//
//      return PHVal;
//    }
//  }
//
//  else if (PHVal > 10.01 && PHVal <= 12.48) {
//    //Serial.println("Enter 7");
//    // PH Value is between 10.01 to 12.48 Call equation function 6 & 7
//    float Val1 = eqn6(temperature_t);
//    float Val2 = eqn7(temperature_t);
//
//    float offVal1 = abs(Val1 - 10.01);        // Get Offset for this Eqn w.r.t. standard value
//    float offVal2 = abs(12.48 - Val2);        // Get Offset for this Eqn w.r.t. standard value
//
//    finalOffset = offVal1 + offVal2 ;
//    finalOffset = finalOffset / 2 ;
//    Serial.print("finalOffset:   ");
//    Serial.println(finalOffset);
//    // If temperature greater than 25 (Calibrated set Temperature) then Subtract final offset from PHVal Else Add offset to it.
//    if (temperature_t > calib_temp) {
//      PHVal = PHVal + finalOffset;
//      return PHVal;
//    } else {
//      PHVal = PHVal - finalOffset;
//      return PHVal;
//    }
//  }
//
//  else if (PHVal > 12.48) {
//    return PHVal ;
//  }
//
//}
//***************************************************************************************    ATC _ FUNCTION ***********************************************************************************
