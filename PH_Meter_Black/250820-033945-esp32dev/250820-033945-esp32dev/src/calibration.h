// Date 27/03/2024
// Purpose  : Amul 3 poin Calibration Issue
// Author : Raza
// Area : In all 3 Point Calibration

//*****************************                             ************************************
//*****************************      CALIBRFATION END       ************************************
////***************************                             ************************************

void cal_curve() {
  //************************    CAL_BUTTON == 51 **********************************
  if (calButton == 51) {
    write_phcal_EEPROM();
    getCoeff(phCalValue, bufferValue, 41);
    writeCoeffIntoEEPROM();
    buf_slope[3] = (((phCalValue[4] - phCalValue[3]) / (bufferValue[4] - bufferValue[3])) / 0.234) * 100;
    data_sender("SLOPE_4", String(buf_slope[3]));
    Serial.println(buf_slope[3]);
    EEPROM.put(444, buf_slope[3]);
    EEPROM.commit();
    fb_flag = 5;
  }
  //*****************************    END  ****************************************






  //************************    CAL_BUTTON == 51 **********************************
  else if (calButton == 11) {
    Serial.println(phCalValue[0]);
    write_phcal_EEPROM();
    getCoeff(phCalValue, bufferValue, 11);
    writeCoeffIntoEEPROM();
    fb_flag = 1;
  }
  //*****************************    END  ****************************************












  //************************    CAL_BUTTON == 21 **********************************
  else if (calButton == 21) {

    // For 3 Point Calibration
    if (cal_mode == 1) {
      getCoeff3(phCalValue3, bufferValue3, 11);
      Serial.println("bufferValue3[0]");
      Serial.println(bufferValue3[0]);
      buf_slope[0] = 0.0;
      data_sender("SLOPE_1", String(buf_slope[0]));
    }
    //         END


    // For 5 Point Calibration
    else if (cal_mode == 2) {
      getCoeff(phCalValue, bufferValue, 11);
      getCoeff(phCalValue, bufferValue, 21);
      buf_slope[0] = (((phCalValue[1] - phCalValue[0]) / (bufferValue[1] - bufferValue[0])) / 0.234) * 100;
      data_sender("SLOPE_1", String(buf_slope[0]));
    }
    //  END
    Serial.println(buf_slope[0]);
    EEPROM.put(426, buf_slope[0]);
    EEPROM.commit();
    Serial.println(phCalValue[1]);
    write_phcal_EEPROM();
    writeCoeffIntoEEPROM();
    fb_flag = 2;
  }
  //*****************************    END  ****************************************







  //************************    CAL_BUTTON == 31 **********************************
  else if (calButton == 31) {
    Serial.println(phCalValue[2]);
    write_phcal_EEPROM();
    if (cal_mode == 1) {
      Serial.println("bufferValue3[1]");
      Serial.println(bufferValue3[1]);
      getCoeff3(phCalValue3, bufferValue3, 11);
      getCoeff3(phCalValue3, bufferValue3, 21);
      buf_slope[1] = (((phCalValue3[1] - phCalValue3[0]) / (bufferValue3[1] - bufferValue3[0])) / 0.234) * 100;
      data_sender("SLOPE_2", String(buf_slope[1]));
    }
    else {
      getCoeff(phCalValue, bufferValue, 21);
      getCoeff(phCalValue, bufferValue, 31);
      buf_slope[1] = (((phCalValue[2] - phCalValue[1]) / (bufferValue[2] - bufferValue[1])) / 0.234) * 100;
      data_sender("SLOPE_2", String(buf_slope[1]));
    }
    writeCoeffIntoEEPROM();
    Serial.println(buf_slope[1]);
    EEPROM.put(432, buf_slope[1]);
    EEPROM.commit();
    fb_flag = 3;
  }
  //*****************************    END  ****************************************










  //************************    CAL_BUTTON == 41 **********************************
  else if (calButton == 41) {
    Serial.println(phCalValue[3]);
    write_phcal_EEPROM();
    if (cal_mode == 1) {
      Serial.println("bufferValue3[2]");
      Serial.println(bufferValue3[2]);
      getCoeff3(phCalValue3, bufferValue3, 21);
      buf_slope[2] = (((phCalValue3[2] - phCalValue3[1]) / (bufferValue3[2] - bufferValue3[1])) / 0.234) * 100;
      data_sender("SLOPE_3", String(buf_slope[2]));
    }
    else if (cal_mode == 2 ) {
      getCoeff(phCalValue, bufferValue, 31);
      getCoeff(phCalValue, bufferValue, 41);
      buf_slope[2] = (((phCalValue[3] - phCalValue[2]) / (bufferValue[3] - bufferValue[2])) / 0.234) * 100;
      data_sender("SLOPE_3", String(buf_slope[2]));
    }
    writeCoeffIntoEEPROM();
    Serial.println(buf_slope[2]);
    EEPROM.put(438, buf_slope[2]);
    EEPROM.commit();
    fb_flag = 4;
  }
}

//*****************************    END  ****************************************




//*****************************                             ************************************
//*****************************      CALIBRFATION END       ************************************
////***************************                             ************************************

















//*****************************************                                       **********************************************
//*****************************************          CAL DATA HANDLING            **********************************************
//*****************************************                                       **********************************************


void cal_data() {
  if ((cal_mode == 1 && fb_flag == 4) || (cal_mode == 2 && fb_flag == 5)) {
    x3 = offset();
    data_sender("OFFSET", String(x3));
    if (cal_mode == 1) {
      slope_total = (buf_slope[2] + buf_slope[3]) / 2;
    }
    if (cal_mode == 2) {
      slope_total = (buf_slope[2] + buf_slope[1] + buf_slope[0] + buf_slope[3]) / 4;
    }
    data_sender("SLOPE", String(slope_total));
    EEPROM.put(420, slope_total);
    EEPROM.commit();
  }
  if (fb_flag == 1)      {
    post1 = pH_update();  data_sender("POST_VAL_1", String(post1));
    fb_flag = 0;
  }
  else if (fb_flag == 2) {
    post2 = pH_update(); data_sender("POST_VAL_2", String(post2));
    fb_flag = 0;
  }
  else if (fb_flag == 3) {
    post3 = pH_update(); data_sender("POST_VAL_3", String(post3));
    fb_flag = 0;
  }
  else if (fb_flag == 4) {
    post4 = pH_update(); data_sender("POST_VAL_4", String(post4));
    fb_flag = 0;
  }
  else if (fb_flag == 5) {
    post5 = pH_update();
    slope_total = (buf_slope[2] + buf_slope[1] + buf_slope[0] + buf_slope[3]) / 4;
    data_sender("POST_VAL_5", String(post5));
    fb_flag = 0;
  }
  if (calButton == 11 || calButton == 21 || calButton == 31 || calButton == 41 || calButton == 51 || calButton == 0) {
    Serial.println("##########################################################");
    Serial.println(calButton);
    Serial.println("##########################################################");
    start_ph_cal = 0;
  }
}
//*****************************************                                       **********************************************
//*****************************************          CAL DATA HANDLING            **********************************************
//*****************************************                                       **********************************************
