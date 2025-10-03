int sensval;

// pH value call and updation
float pH_update() {

  //if(atc_var == 0)
  x =  readpH();

  //else x = atc_fn();
  x = round(x * 100) / 100;
  //pH range exception
  if (x < 0 || x > 14) x = 0.00;
  delay(200);
  //  Serial.print("Final pH:    ");
  //  Serial.println(x);
  //  Serial.print("                ");
  // if (WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2006/Data/PH_VAL", x);
  data_sender("PH_VAL", String(x));
  return x;
}

void hold() {

  if (x_prev == pH_read) {
    // if (WIFI_FLAG == 1) .setInt(firebaseData, "/PHMETER/EPT2006/Data/HOLD", 1);
    data_sender("HOLD", String(1));
    hodl = 1;
  }
  else {
    // if (WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2006/Data/HOLD", 0);
    data_sender("HOLD", String(0));
    hodl = 0;

  }

  //3 second data logging for comparison
  if (currentMillis_pH - previous_pH > 3000) {
    previous_pH = currentMillis_pH;
    x_prev = pH_read;
  }
}


// mV value call and updation
void mV_update() {
  //  if (WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2006/Data/TDS_VAL", volt);
  data_sender("VOLT", String(volt));
  mVx = 59.16 * x - 414.12;
  //  //  if (WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2006/Data/EC_VAL", mVx);
  data_sender("EC_VAL", String(mVx));
}

// slope formula
float slope() {

  float slope = 0.2357;
  float id_slope = ((abs(phCalValue[2] - phCalValue[1]) / 3) / slope) * 100;
  return id_slope;
}

// offset formula
float offset() {
  float offset_ = abs(1.65 - phCalValue[2]);
  return offset_;
}