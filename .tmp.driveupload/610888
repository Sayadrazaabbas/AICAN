//#define BATTERY 32
// Analog battery pin
int sensval;
// pH value call and updation
float pH_update() {
  //if(atc_var == 0)
  x = readpH();
  //else x = atc_fn();
  x = round(x * 100) / 100;
  //pH range exception
  if (x < 0 || x > 14) x = 0.00;
  Serial.print("Final pH:    ");
  Serial.println(x);
  //  if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/PH_VAL", x);
  if (currentMillis - lastPHPublish >= PUBLISH_INTERVAL) {
    snprintf(Ph_val, sizeof(Ph_val), "%f", x);
    client.publish(PH_VAL.c_str(), Ph_val);  //##############################################################
    if (x_prev == pH_read) {
      client.publish(HOld.c_str(), "1");
      hodl = 1;
    } else {
      client.publish(HOld.c_str(), "0");
      hodl = 0;
    }
    x_prev = pH_read;
    lastPHPublish = currentMillis;
  }
  return x;
}





//
//void hold() {
//  if (x_prev == pH_read) {
//    //    if(WIFI_FLAG == 1) Firebase.setInt(firebaseData, "/PHMETER/EPT2021/Data/HOLD", 1);
////    if (currentMillis - lastHOLDPublish >= PUBLISH_INTERVAL) {
//      client.publish(HOld.c_str(), "1"); //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
////      delay(500);
////      lastHOLDPublish = currentMillis;
////    }
//    hodl = 1;
//
//  }
//  else {
//      if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/HOLD", 0);
//
//    hodl = 0;
//    client.publish(HOld.c_str(), "0"); //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//  }
//
//  //3 second data logging for comparison
//  if (currentMillis_pH - previous_pH > 3000) {
////    x_prev = pH_read;
//    previous_pH = currentMillis_pH;
//
//  }
//}



// mV value call and updation
void mV_update() {
  //  if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/TDS_VAL", volt);
  mVx = mV_calc(volt);
  //  if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/Data/EC_VAL", mVx);
  if (currentMillis - lastMVPublish >= PUBLISH_INTERVAL) {
    snprintf(Mv_val, sizeof(Mv_val), "%f", mVx);
    client.publish(MV_VAL.c_str(), Mv_val);  //###########################################################
    lastMVPublish = currentMillis;           // Update the last publish time
  }

  //delay(10);
}



// battery percentage values curve and updation
void battery() {
  int raw = ads_read_bat();
  volt = (float)raw * 0.125 / 1000;

  Serial.println("Battery:    ");
  Serial.println(volt);
  y = -(1100.688) + (1117.027 * volt) - (251.13 * volt * volt);
  if (y < 1) y = 0;
  else if (y > 100) y = 100;
  //  if(WIFI_FLAG == 1) Firebase.setInt(firebaseData, "/PHMETER/EPT2021/Data/BATTERY", y);
  snprintf(Battery, sizeof(Battery), "%d", y);
  client.publish(BATTERY.c_str(), Battery);  //######################################################
  client.publish("/EPT2025/STATUS", "1");
  delay(10);
}

// slope formula
float slope() {
  float id_slope;
  if (cal_mode == 2) id_slope = (buf_slope[0] + buf_slope[1] + buf_slope[2] + buf_slope[3]) / 4;
  else id_slope = (buf_slope[1] + buf_slope[2]) / 2;
  slope_total = id_slope;
  return id_slope;
}

// offset formula
float offset() {
  float offset_ = mV_calc(1.93);  // snprintf(Offset,sizeof(Offset),"%f",offset);// client.publish(OFFSET,Offset);
  return offset_;
}
