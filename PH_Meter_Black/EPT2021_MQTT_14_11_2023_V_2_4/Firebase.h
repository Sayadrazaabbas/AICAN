////#include <FirebaseESP32.h>
//#define FIREBASE_HOST "https://labdevices-8c9a5-default-rtdb.asia-southeast1.firebasedatabase.app/"
//#define FIREBASE_AUTH "ua38oW7tWnMul9wFJlutzXlCYP7vEuAroYkQ0Eu8"
//String path = "/PHMETER/EPT2001";
//
//void printResult(StreamData &data);
//
//void streamCallback(StreamData data) {
//
//  yield();
//    if (data.dataPath() == "/UI/PH/PH_CAL/CAL_MODE") {
//    cal_mode = data.intData();
//    EEPROM.put(410, cal_mode);
//    EEPROM.commit();
//    Serial.println("cal_mode:");
//    Serial.print(cal_mode);
//    }
//
//    if (data.dataPath() == "/Data/ATC") {
//    atc_var = data.intData();
//    Serial.println("atc_var: ");
//    Serial.println(atc_var);
//    }
//
//    if (data.dataPath() == "/Data/T_SET") {
//    Ro = data.intData();
//    EEPROM.put(450, Ro);
//    EEPROM.commit();
//    }
//
//    if (data.dataPath() == "/Data/ATC_AT") {
//    manual_atc = data.floatData();
//    for(int i=0; i<=4; i++){
//      atcbufferValue[i] = compen_pH(bufferValue[i],i);
//      Serial.println("ATC Buffer ");
//      Serial.print(i);
//      Serial.print(":");
//      Serial.print(atcbufferValue[i]);
//      delay(100);
//      }
//    //if(cal_mode == 1) getCoeff_ATC(phCalValue, bufferValue, atcbufferValue, 1, 1);
//    //else {getCoeff_ATC(phCalValue, bufferValue, atcbufferValue, 2, 1); getCoeff_ATC(phCalValue, bufferValue, atcbufferValue, 2, 2);}
//    Serial.println("manual_atc: ");
//    Serial.println(manual_atc);
//    }
//
////    if(data.dataPath() == "/Data/CFR"){
////    cfr_select = data.intData();
////    Serial.println("CFR: ");
////    Serial.println(cfr_select);   
////    }
//
//    if(data.dataPath() == "/MANUAL"){
//    manual_calibration_flag = data.intData();
//    Serial.println("Manual Calibration Enabled");
//    EEPROM.put(460, manual_calibration_flag);
//    EEPROM.commit();
//    }
//    
//    if(data.dataPath() == "/Data/AUTOLOG"){
//    log_mode = data.intData();
//    Serial.println("Now in log mode");  
//    }
//
////    if(data.dataPath() == "/UI/PH/PH_CAL/maxMV1"){maxMV[0] = data.floatData();}
////    if(data.dataPath() == "/UI/PH/PH_CAL/maxMV2"){maxMV[1] = data.floatData();}
////    if(data.dataPath() == "/UI/PH/PH_CAL/maxMV3"){maxMV[2] = data.floatData();}
////    if(data.dataPath() == "/UI/PH/PH_CAL/maxMV4"){maxMV[3] = data.floatData();}
////    if(data.dataPath() == "/UI/PH/PH_CAL/maxMV5"){maxMV[4] = data.floatData();}
////
////    if(data.dataPath() == "/UI/PH/PH_CAL/minMV1"){minMV[0] = data.floatData();}
////    if(data.dataPath() == "/UI/PH/PH_CAL/minMV2"){minMV[1] = data.floatData();}
////    if(data.dataPath() == "/UI/PH/PH_CAL/minMV3"){minMV[2] = data.floatData();}
////    if(data.dataPath() == "/UI/PH/PH_CAL/minMV4"){minMV[3] = data.floatData();}
////    if(data.dataPath() == "/UI/PH/PH_CAL/minMV5"){minMV[4] = data.floatData();}
//    
//    if (data.dataPath() == "/UI/PH/PH_CAL/CAL") {
//    calButton = data.intData();
//    Serial.println(calButton);
//
//   if (calButton == 10 || calButton == 20 || calButton == 30 || calButton == 40 || calButton == 50) {      
//      start_ph_cal = 1;
//    }
//
//    
//  
//    if (calButton == 0) {
//      start_ph_cal = 0;
//    }    
//  }
//  //BUFFERS///////////
//  //char num[5];
//  else if (data.dataPath() == "/UI/PH/PH_CAL/B_1") {
//    bufferValue[0] = data.stringData().toFloat();
//    
//    write_buffer_EEPROM();
//    Serial.println(bufferValue[0]);
//  }
//  else if (data.dataPath() == "/UI/PH/PH_CAL/B_2") {
////    bufferValue[1] = data.floatData();
//    bufferValue[1]=data.stringData().toFloat();
//    write_buffer_EEPROM();
//    Serial.println(bufferValue[1]);
//  }
//  else if (data.dataPath() == "/UI/PH/PH_CAL/B_3") {
////    bufferValue[2] = data.floatData();
//      bufferValue[2]=data.stringData().toFloat();
//      write_buffer_EEPROM();
//    Serial.println(bufferValue[2]);
//  }
//  else if (data.dataPath() == "/UI/PH/PH_CAL/B_4") {
////    bufferValue[3] = data.floatData();
//    bufferValue[3]=data.stringData().toFloat();
//    write_buffer_EEPROM();
//    Serial.println(bufferValue[3]);
//  }
//  else if (data.dataPath() == "/UI/PH/PH_CAL/B_5") {
//   // num[] = data.floatData();
//    bufferValue[4]=data.stringData().toFloat();
//    write_buffer_EEPROM();
//    Serial.println(bufferValue[4]);
//  }
//
//  
//  else if (data.dataPath() == "/UI/PH/PH_CAL/COEFF_A") {
//    phCalCoeff[0] = data.floatData();
//    writeCoeffIntoEEPROM();
//    Serial.println(phCalCoeff[0]);
//  }
//  else if (data.dataPath() == "/UI/PH/PH_CAL/COEFF_B") {
//    phCalCoeff[1] = data.floatData();
//    writeCoeffIntoEEPROM();
//    Serial.println(phCalCoeff[1]);
//  }
//    else if (data.dataPath() == "/UI/PH/PH_CAL/COEFF_C") {
//    phCalCoeff[2] = data.floatData();
//    writeCoeffIntoEEPROM();
//    Serial.println(phCalCoeff[2]);
//  }
//      else if (data.dataPath() == "/UI/PH/PH_CAL/COEFF_D") {
//    phCalCoeff[3] = data.floatData();
//    writeCoeffIntoEEPROM();
//    Serial.println(phCalCoeff[3]);
//  }
//}
//
//
//void printResult(StreamData &data)
//{
//
//  if (data.dataType() == "int")
//    Serial.println(data.intData());
//  else if (data.dataType() == "float")
//    Serial.println(data.floatData(), 5);
//  else if (data.dataType() == "double")
//    printf("%.9lf\n", data.doubleData());
//  else if (data.dataType() == "boolean")
//    Serial.println(data.boolData() == 1 ? "true" : "false");
//  else if (data.dataType() == "string" || data.dataType() == "null")
//    Serial.println(data.stringData());
//}
//
//void streamTimeoutCallback(bool timeout)
//{
//  if (timeout)
//  {
//    Serial.println();
//    Serial.println("Stream timeout, resume streaming...");
//    Serial.println();
//  }
//}
//
//
//void firebase_initialization() {
//
//  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//
//
//  if (!Firebase.beginStream(fbdo1, path))
//  {
//    Serial.println("------------------------------------");
//    Serial.println("Can't begin stream connection...");
//    Serial.println("REASON: " + fbdo1.errorReason());
//    Serial.println("------------------------------------");
//    Serial.println();
//  }
//
//  Firebase.setStreamCallback(fbdo1, streamCallback, streamTimeoutCallback);
//}
