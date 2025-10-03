#include <Button.h>

Button button1(14); // UP
Button button2(13); // DOWN
Button button3(15); // OK

int start_millis  = 0; // acceleration timer

float count = 0;


void button_init() {
  button1.begin();
  button2.begin();
  button3.begin();
}

float button_acceleration() {
  if (button1.pressed()) {
    start_millis = millis();
    count = count + 0.01;
  }

  if (button2.pressed()) {
    start_millis = millis();
    count = count - 0.01;
  }

  if (millis() - start_millis > 1000) {
    while (button1.read() == Button::PRESSED) {
      count = count + 0.01;
      delay(50);

    }
  }

  if (millis() - start_millis > 1000) {
    while (button2.read() == Button::PRESSED) {
      count = count - 0.01;
      delay(50);

    }
  }
  return count;
}

void cal_button_check() {


  while (button3.pressed()) {
    manual_cal_mode = 1;
    Serial.println("manual_cal_mode: ");
    Serial.println(manual_cal_mode);
  }
  Serial.println("exit cal_button_check");

}
void buffer_check() {
  int buffer_millis =  millis();
  if (button3.pressed()) {
    if (change_buffer == 1) {
      change_buffer = 0;

      if (buffer_pointer == 10) buffer_pointer = 11;
      if (buffer_pointer == 20) buffer_pointer = 21;
      if (buffer_pointer == 30) buffer_pointer = 31;
      if (buffer_pointer == 40) buffer_pointer = 41;
      if (buffer_pointer == 50) buffer_pointer = 51;
    }
    else change_buffer = 1;
  }

  Serial.println("change_buffer:");
  Serial.println(change_buffer);
  Serial.println("buffer_pointer: ");
  Serial.println(buffer_pointer);
}

void buffer_mov() {
  Serial.println("enter buffer_mov");
  if (button3.pressed()) {
    if (cal_mode == 2) {
      if (buffer_pointer == 0) buffer_pointer = 10;
    }
    else {
      if (buffer_pointer == 0) buffer_pointer = 20;
    }
    Serial.println("buffer pointer: ");
    Serial.println(buffer_pointer);
  }
  if (button2.pressed()) {
    if (buffer_pointer == 0) manual_cal_mode = 0;
  }
}

void buffer_page() {
  Serial.println("enter buffer_page");
  cal_home();
  while (buffer_pointer == 10) {
    Serial.println("buffer_pointer in 10");
    buffer_check();
    while (change_buffer == 1) {
      add_val1 = bufferValue[0];
      add_val1 = add_val1 + button_acceleration();
      Serial.print("add_val1: ");
      Serial.println(add_val1);
      buffer_check();
      runner_val(1, add_val1);
    }
    count = 0;
    buf_run(1, add_val1);
    bufferValue[0] = add_val1;
    Serial.println("bufferValue: ");
    Serial.println(bufferValue[0]);

  }
  while (buffer_pointer == 20) {
    Serial.println("buffer_pointer in 20");
    buffer_check();
    while (change_buffer == 1) {
      add_val2 = bufferValue[1];
      add_val2 = add_val2 + button_acceleration();
      Serial.print("add_val2: ");
      Serial.println(add_val2);
      buffer_check();
      runner_val(2, add_val2);
    }
    count = 0;
    buf_run(2, add_val2);
    bufferValue[1] = add_val2;
    Serial.println("bufferValue: ");
    Serial.println(bufferValue[1]);
  }

  while (buffer_pointer == 30) {
    Serial.println("buffer_pointer in 30");
    buffer_check();
    while (change_buffer == 1) {
      add_val3 = bufferValue[2];
      add_val3 = add_val3 + button_acceleration();
      Serial.print("add_val3: ");
      Serial.println(add_val3);
      buffer_check();
      runner_val(3, add_val3);
    }
    count = 0;
    buf_run(3, add_val3);
    bufferValue[2] = add_val3;
    Serial.println("bufferValue: ");
    Serial.println(bufferValue[2]);
  }

  while (buffer_pointer == 40) {
    buffer_check();
    Serial.println("buffer_pointer in 40");
    while (change_buffer == 1) {
      add_val4 = bufferValue[3];
      add_val4 = add_val4 + button_acceleration();
      Serial.print("add_val4: ");
      Serial.println(add_val4);
      buffer_check();
      runner_val(4, add_val4);
    }
    count = 0;
    buf_run(4, add_val4);
    bufferValue[3] = add_val4;
    Serial.println("bufferValue: ");
    Serial.println(bufferValue[3]);
  }
  while (buffer_pointer == 50) {
    buffer_check();
    Serial.println("buffer_pointer in 50");
    while (change_buffer == 1) {
      add_val5 = bufferValue[4];
      add_val5 = add_val5 + button_acceleration();
      Serial.print("add_val5: ");
      Serial.println(add_val5);
      buffer_check();
      runner_val(5, add_val5);
    }
    count = 0;
    buf_run(5, add_val5);
    bufferValue[4] = add_val5;
    Serial.println("bufferValue: ");
    Serial.println(bufferValue[4]);
  }
  write_buffer_EEPROM();
}

void timer_page() {

  int start_time = millis();
  while (buffer_pointer == 11) {

    int countdown = (millis() - start_time);
    Serial.println("countdown: ");
    Serial.println(countdown);
    phCalValue[0] = readCalpH();
    display_cal_timer(countdown);
    //    if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/VAL_1", phCalValue[0]);
    //*********************************************************************************************//
    snprintf(val_1, sizeof(val_1), "%f", phCalValue[0]);
    client.publish(VAL_1.c_str(), val_1);
    if (countdown  > 45000) {
      getCoeff(phCalValue, bufferValue, 11);
      writeCoeffIntoEEPROM();
      buffer_pointer = 20;
    }
  }
  while (buffer_pointer == 21) {

    int countdown = (millis() - start_time);
    Serial.println("countdown: ");
    Serial.println(countdown);
    phCalValue[1] = readCalpH();
    //    if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/VAL_2", phCalValue[1]);
    //*****************************************************************************************************
    snprintf(val_2, sizeof(val_2), "%f", phCalValue[1]);
    client.publish(VAL_2.c_str(), val_2);
    display_cal_timer(countdown);
    if (countdown  > 45000) {
      if (cal_mode == 2) {
        getCoeff(phCalValue, bufferValue, 11);
        getCoeff(phCalValue, bufferValue, 21);
      }
      else getCoeff(phCalValue3, bufferValue3, 21);
      writeCoeffIntoEEPROM();
      buffer_pointer = 30;
    }
  }
  while (buffer_pointer == 31) {
    int countdown = millis() - start_time;
    Serial.println("countdown: ");
    Serial.println(countdown);
    phCalValue[2] = readCalpH();
    //    if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/VAL_3", phCalValue[2]);
    //*****************************************************************************************************
    snprintf(val_3, sizeof(val_3), "%f", phCalValue[2]);
    client.publish(VAL_3.c_str(), val_3);
    display_cal_timer(countdown);
    if (countdown  > 45000) {
      if (cal_mode == 2) {
        getCoeff(phCalValue, bufferValue, 21);
        getCoeff(phCalValue, bufferValue, 31);
      }
      else {
        getCoeff(phCalValue3, bufferValue3, 21);
        getCoeff(phCalValue3, bufferValue3, 31);
      }
      writeCoeffIntoEEPROM();
      buffer_pointer = 40;
    }
  }
  while (buffer_pointer == 41) {
    int countdown = millis() - start_time;
    Serial.println("countdown: ");
    Serial.println(countdown);
    phCalValue[3] = readCalpH();
    //    if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/VAL_4", phCalValue[3]);
    //******************************************************************************************************
    snprintf(val_4, sizeof(val_4), "%f", phCalValue[3]);
    client.publish(VAL_4.c_str(), val_4);
    
    display_cal_timer(countdown);
    if (countdown  > 45000) {
      if (cal_mode == 2) {
        getCoeff(phCalValue, bufferValue, 31);
        getCoeff(phCalValue, bufferValue, 41);
        writeCoeffIntoEEPROM();
        buffer_pointer = 50;
      }
      else {
        getCoeff(phCalValue3, bufferValue3, 31);
        writeCoeffIntoEEPROM();
        buffer_pointer = 0;
        manual_cal_mode = 0;
      }

    }
  }
  while (buffer_pointer == 51) {
    int countdown = millis() - start_time;
    Serial.println("countdown: ");
    Serial.println(countdown);
    phCalValue[4] = readCalpH();
    //    if(WIFI_FLAG == 1) Firebase.setFloat(firebaseData, "/PHMETER/EPT2021/UI/PH/PH_CAL/VAL_5", phCalValue[4]);
    //******************************************************************************************************
    snprintf(val_5, sizeof(val_5), "%f", phCalValue[4]);
    client.publish(VAL_5.c_str(), val_5);

    
    display_cal_timer(countdown);
    if (countdown  > 45000) {
      getCoeff(phCalValue, bufferValue, 41);
      writeCoeffIntoEEPROM();
      buffer_pointer = 0;
      manual_cal_mode = 0;
    }
  }
}

void manual_calibration() {
  Serial.println("enter manual_calibration");
  while (manual_cal_mode == 1) {
    buffer_mov();
    buffer_page();
    timer_page();
  }
}
