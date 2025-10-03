void cal_curve() {
  if (calButton == 51) {
    //    if (Firebase.getFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/VAL_5")) phCalValue[4] = firebaseData.floatData();
    snprintf(val_5, sizeof(val_5), "%f", phCalValue[4]);///////////#######################
    client.publish(VAL_5.c_str(), val_5);///////////////////////////////#######################
    Serial.println(phCalValue[4]);
    write_phcal_EEPROM();
    getCoeff(phCalValue, bufferValue, 41);
    writeCoeffIntoEEPROM();
    buf_slope[3] = (((phCalValue[4] - phCalValue[3]) / (bufferValue[4] - bufferValue[3])) / 0.234) * 100;


    //    if (WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/SLOPE_4", buf_slope[3]);
    snprintf(slope_4, sizeof(slope_4), "%f", buf_slope[3]);
    client.publish(SLOPE_4.c_str(), slope_4); //#########################################

    Serial.println(buf_slope[3]);
    EEPROM.put(444, buf_slope[3]);
    EEPROM.commit();
    fb_flag = 5;
  }
  else if (calButton == 11) {
    //    if (Firebase.getFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/VAL_1")) phCalValue[0] = firebaseData.floatData();
    snprintf(val_1, sizeof(val_1), "%f", phCalValue[0]);
    client.publish(VAL_1.c_str(), val_1);//#############################################
    Serial.println(phCalValue[0]);
    write_phcal_EEPROM();
    getCoeff(phCalValue, bufferValue, 11);
    writeCoeffIntoEEPROM();
    fb_flag = 1;
  }
  else if (calButton == 21) {
    //    if (Firebase.getFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/VAL_2")) phCalValue[1] = firebaseData.floatData();
    snprintf(val_2, sizeof(val_2), "%f", phCalValue[1]);
    client.publish(VAL_2.c_str(), val_2);
    Serial.println(phCalValue[1]);
    write_phcal_EEPROM();


    if (cal_mode == 1) getCoeff(phCalValue3, bufferValue3, 21);
    else {
      getCoeff(phCalValue, bufferValue, 11);
      getCoeff(phCalValue, bufferValue, 21);
    }
    writeCoeffIntoEEPROM();
    buf_slope[0] = (((phCalValue[1] - phCalValue[0]) / (bufferValue[1] - bufferValue[0])) / 0.234) * 100;
    //    if (WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/SLOPE_1", buf_slope[0]);
    snprintf(slope_1, sizeof(slope_1), "%f", buf_slope[0]);
    client.publish(SLOPE_1.c_str(), slope_1); //##########################################

    Serial.println(buf_slope[0]);
    EEPROM.put(426, buf_slope[0]);
    EEPROM.commit();
    fb_flag = 2;
  }
  else if (calButton == 31) {
    //    if (Firebase.getFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/VAL_3")) phCalValue[2] = firebaseData.floatData();
    Serial.println(phCalValue[2]);
    snprintf(val_3, sizeof(val_3), "%f", phCalValue[2]);
    client.publish(VAL_3.c_str(), val_3);//#############################################
    write_phcal_EEPROM();
    if (cal_mode == 1) {
      getCoeff(phCalValue3, bufferValue3, 21);
      getCoeff(phCalValue3, bufferValue3, 31);
    }
    else {
      getCoeff(phCalValue, bufferValue, 21);
      getCoeff(phCalValue, bufferValue, 31);
    }
    writeCoeffIntoEEPROM();
    buf_slope[1] = (((phCalValue[2] - phCalValue[1]) / (bufferValue[2] - bufferValue[1])) / 0.234) * 100;
    //    if (WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/SLOPE_2", buf_slope[1]);
    snprintf(slope_2, sizeof(slope_2), "%f", buf_slope[1]);
    client.publish(SLOPE_2.c_str(), slope_2); //########################################
    Serial.println(buf_slope[1]);
    EEPROM.put(432, buf_slope[1]);
    EEPROM.commit();
    fb_flag = 3;
  }

  else if (calButton == 41) {
    //    if (Firebase.getFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/VAL_4")) phCalValue[3] = firebaseData.floatData();
    Serial.println(phCalValue[3]);
    snprintf(val_4, sizeof(val_4), "%f", phCalValue[3]);
    client.publish(VAL_4.c_str(), val_4);//##########################################
    write_phcal_EEPROM();
    if (cal_mode == 1) {
      getCoeff(phCalValue3, bufferValue3, 31);
    }
    else {
      getCoeff(phCalValue, bufferValue, 31);
      getCoeff(phCalValue, bufferValue, 41);
    }
    writeCoeffIntoEEPROM();
    buf_slope[2] = (((phCalValue[3] - phCalValue[2]) / (bufferValue[3] - bufferValue[2])) / 0.234) * 100;
    //    if (WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/SLOPE_3", buf_slope[2]);

    snprintf(slope_3, sizeof(slope_3), "%f", buf_slope[2]);
    client.publish(SLOPE_3.c_str(), slope_3); //####################################

    Serial.println(buf_slope[2]);
    EEPROM.put(438, buf_slope[2]);
    EEPROM.commit();
    fb_flag = 4;
  }
}

void cal_data() {
  //  if ((cal_mode == 1 && fb_flag == 4) || (cal_mode == 2 && fb_flag == 5)) {
  if ((cal_mode == 1 && fb_flag == 4) || (cal_mode == 2 && fb_flag == 5)) {
    float slope_total = slope();
    snprintf(Slope, sizeof(Slope), "%f", slope_total);
    Serial.println("SLOPE MAIN");
    Serial.println(Slope);
    client.publish(SLOPE.c_str(), Slope);//############################################
    x3 = offset();
    //    Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/OFFSET", x3);
    snprintf(Offset, sizeof(Offset), "%f", x3);
    client.publish(OFFSET.c_str(), Offset); //###################################
    Serial.print("Publishing OFFSET: ");
    Serial.println(Offset);
    //    Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/SLOPE", slope_total);
    Serial.println("############  offset published ##################");
    //delay(100);
    EEPROM.put(420, slope_total);
    EEPROM.commit();
  }
  if (fb_flag == 1)      {
    post1 = pH_update();
    //    Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/POST_VAL_1", post1);
    snprintf(post_val_1, sizeof(post_val_1), "%f", post1);
    client.publish(POST_VAL_1.c_str(), post_val_1);//#########################################
    snprintf(temp_val_1, sizeof(temp_val_1), "%f", vals);
    client.publish(TEMP_VAL_1.c_str(), temp_val_1); //#########################################
    fb_flag = 0;
  }
  else if (fb_flag == 2) {
    post2 = pH_update();
    //    Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/POST_VAL_2", post2);
    snprintf(post_val_2, sizeof(post_val_2), "%f", post2);
    client.publish(POST_VAL_2.c_str(), post_val_2);//#########################################
    snprintf(temp_val_2, sizeof(temp_val_2), "%f", vals);
    client.publish(TEMP_VAL_2.c_str(), temp_val_2); //#########################################

    fb_flag = 0;
  }
  else if (fb_flag == 3) {
    post3 = pH_update();
    //    Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/POST_VAL_3", post3);
    snprintf(post_val_3, sizeof(post_val_3), "%f", post3);
    client.publish(POST_VAL_3.c_str(), post_val_3);//#########################################
    snprintf(temp_val_3, sizeof(temp_val_3), "%f", vals);
    client.publish(TEMP_VAL_3.c_str(), temp_val_3); //#########################################
    fb_flag = 0;
  }
  else if (fb_flag == 4) {
    post4 = pH_update();
    //    Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/POST_VAL_4", post4);
    snprintf(post_val_4, sizeof(post_val_4), "%f", post4);
    client.publish(POST_VAL_4.c_str(), post_val_4);//#########################################
    snprintf(temp_val_4, sizeof(temp_val_4), "%f", vals);
    client.publish(TEMP_VAL_4.c_str(), temp_val_4); //#########################################
    fb_flag = 0;
  }
  else if (fb_flag == 5) {
    post5 = pH_update();
    //    Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/POST_VAL_5", post5);
    snprintf(post_val_5, sizeof(post_val_5), "%f", post5);
    client.publish(POST_VAL_5.c_str(), post_val_5);//#########################################
    snprintf(temp_val_5, sizeof(temp_val_5), "%f", vals);
    client.publish(TEMP_VAL_5.c_str(), temp_val_5); //#########################################
    offset();
    delay(100);
    fb_flag = 0;
  }
  if (calButton == 11 || calButton == 21 || calButton == 31 || calButton == 41 || calButton == 51) start_ph_cal = 0;
}
