#include <Button.h>
#include "curvefit.h"
unsigned long previousMillis1 = 0; // variable to store the last time the code block was executed
Button button1(19); // UP
Button button2(4); // DOWN
Button button3(14); // OK
int start_millis  = 0; // acceleration timer
float count = 0;
void probe_manual();
void button_init() {
  button1.begin();
  button2.begin();
  button3.begin();
}

void incr() {
  unsigned long currentMillis1 = millis(); // get the current time
  if (currentMillis1 - previousMillis1 >= 3000) { // check if the interval has passed
    previousMillis1 = currentMillis1; // save the current time
    increment = increment + 0.01;
  }
}


float button_acceleration() {
  increment = 0.01;
  if (button1.pressed()) {
    Serial.println("B1 " + String(increment));
    start_millis = millis();
    count = count + 0.01;
    buz_flag = 1;
  }

  if (button2.pressed()) {
    start_millis = millis();
    count = count - 0.01;
    Serial.println("B2 " + String(increment));
    buz_flag = 1;
  }


  if (millis() - start_millis > 1000) {
    while (button1.read() == Button::PRESSED) {
      count = count + increment;
      buz_flag = 1;
      Serial.println("INCR " + String(increment));
      incr();
      if (buffer_pointer == 10) runner_val(1, add_val1 + count);
      if (buffer_pointer == 20) runner_val(2, add_val2 + count);
      if (buffer_pointer == 30) runner_val(3, add_val3 + count);
      if (buffer_pointer == 40) runner_val(4, add_val4 + count);
      if (buffer_pointer == 50) runner_val(5, add_val5 + count);
      delay(50);
    }
  }
  if (millis() - start_millis > 1000) {
    while (button2.read() == Button::PRESSED) {
      incr();
      buz_flag = 1;
      count = count - increment;
      Serial.println("DNCR " + String(increment));
      if (buffer_pointer == 10) runner_val(1, add_val1 + count);
      if (buffer_pointer == 20) runner_val(2, add_val2 + count);
      if (buffer_pointer == 30) runner_val(3, add_val3 + count);
      if (buffer_pointer == 40) runner_val(4, add_val4 + count);
      if (buffer_pointer == 50) runner_val(5, add_val5 + count);
      delay(50);
    }
  }
  return count;

  Serial.println("RESET " + String(increment));
}





void cal_button_check() {
  while (button3.pressed()) {
    if (log_mode == 0) {
      manual_cal_mode = 1;
      Serial.println("cal_mode: ");
      Serial.println(cal_mode);
      buz_flag = 1;
    }
  }
  Serial.println("exit cal_button_check");
}



void buffer_check() {
  int buffer_millis =  millis();
  if (button3.pressed()) {
    Serial.println("enter buffer_page");
    buz_flag = 1;
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
  //  Serial.println("change_buffer:");
  //  Serial.println(change_buffer);
  //  Serial.println("buffer_pointer: ");
  //  Serial.println(buffer_pointer);
}



void buffer_mov() {
  Serial.println("enter buffer_mov");
  if (button3.pressed()) {
    buz_flag = 1;
    cal_mode = 1;
    EEPROM.put(410, cal_mode); EEPROM.commit();
    Serial.println("Buffer move cal_mode = " + String(cal_mode));
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
    buz_flag = 1;
    if (buffer_pointer == 0) manual_cal_mode = 0;
  }
}




void buffer_page() {
  Serial.println("enter buffer_page");
  cal_home();
  Serial.println("buffer_pointer" + String(buffer_pointer));
  while (buffer_pointer == 10) {
    Serial.println("buffer_pointer in 10");
    buffer_check();
    while (change_buffer == 1) {
      add_val1 = bufferValue[0];
      Serial.println("bufferValue[0]");
      Serial.println(bufferValue[0]);
      Serial.println(add_val1);
      Serial.println("add_val1");
      add_val1 = add_val1 + button_acceleration();
      //      Serial.print("add_val1: ");
      //      Serial.println(add_val1);
      buffer_check();
      runner_val(1, add_val1);
    }
    count = 0;
    buf_run(1, add_val1);
    bufferValue[0] = add_val1;
    //    Serial.println("bufferValue: ");
    //    Serial.println(bufferValue[0]);

  }
  while (buffer_pointer == 20) {
    Serial.println("buffer_pointer in 20");
    buffer_check();
    while (change_buffer == 1) {
      add_val2 = bufferValue[1];
      add_val2 = add_val2 + button_acceleration();
      //      Serial.print("add_val2: ");
      //      Serial.println(add_val2);
      buffer_check();
      runner_val(2, add_val2);
    }
    count = 0;
    buf_run(2, add_val2);
    bufferValue[1] = add_val2;
    //    Serial.println("bufferValue: ");
    //    Serial.println(bufferValue[1]);
  }
  while (buffer_pointer == 30) {
    Serial.println("buffer_pointer in 30");
    buffer_check();
    while (change_buffer == 1) {
      add_val3 = bufferValue[2];
      add_val3 = add_val3 + button_acceleration();
      //      Serial.print("add_val3: ");
      //      Serial.println(add_val3);
      buffer_check();
      runner_val(3, add_val3);
    }
    count = 0;
    buf_run(3, add_val3);
    bufferValue[2] = add_val3;
    //    Serial.println("bufferValue: ");
    //    Serial.println(bufferValue[2]);
  }

  while (buffer_pointer == 40) {
    buffer_check();
    Serial.println("buffer_pointer in 40");
    while (change_buffer == 1) {
      add_val4 = bufferValue[3];
      add_val4 = add_val4 + button_acceleration();
      //      Serial.print("add_val4: ");
      //      Serial.println(add_val4);
      buffer_check();
      runner_val(4, add_val4);
    }
    count = 0;
    buf_run(4, add_val4);
    bufferValue[3] = add_val4;
    //    Serial.println("bufferValue: ");
    //    Serial.println(bufferValue[3]);
  }
  while (buffer_pointer == 50) {
    buffer_check();
    Serial.println("buffer_pointer in 50");
    while (change_buffer == 1) {
      add_val5 = bufferValue[4];
      add_val5 = add_val5 + button_acceleration();
      //      Serial.print("add_val5: ");
      //      Serial.println(add_val5);
      buffer_check();
      runner_val(5, add_val5);
    }
    count = 0;
    buf_run(5, add_val5);
    bufferValue[4] = add_val5;
  }
  write_buffer_EEPROM();
}






void timer_page() {
  Serial.println("IN Timer Page ");
  int start_time = millis();
  while (buffer_pointer == 11) {
    int countdown = (millis() - start_time);
    //    Serial.println("countdown: ");
    //    Serial.println(countdown, 2);
    phCalValue[0] = readCalpH();
    display_cal_timer(countdown);
    if (countdown  > 45000) {
      getCoeff(phCalValue, bufferValue, 11);
      writeCoeffIntoEEPROM();
      buffer_pointer = 20;
    }
  }
  while (buffer_pointer == 21) {
    int countdown = (millis() - start_time);
    //    Serial.println("countdown: ");
    //    Serial.println(countdown, 2);
    //    Serial.println(countdown);
    phCalValue[1] = readCalpH();
    display_cal_timer(countdown);
    if (countdown  > 45000) {
      if (cal_mode == 2) {
        getCoeff(phCalValue, bufferValue, 11);
        getCoeff(phCalValue, bufferValue, 21);
      }
      else getCoeff(phCalValue3, bufferValue3, 21);
      buf_slope[0] = (((phCalValue[1] - phCalValue[0]) / (bufferValue[1] - bufferValue[0])) / 0.234) * 100;
      //      Serial.println(buf_slope[0]);
      EEPROM.put(426, buf_slope[0]);
      EEPROM.commit();
      writeCoeffIntoEEPROM();
      buffer_pointer = 30;
    }
  }
  while (buffer_pointer == 31) {
    int countdown = millis() - start_time;
    //    Serial.println(countdown, 2);
    //    Serial.println("countdown: ");
    //    Serial.println(countdown);
    phCalValue[2] = readCalpH();
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
      buf_slope[1] = (((phCalValue[2] - phCalValue[1]) / (bufferValue[2] - bufferValue[1])) / 0.234) * 100;
      EEPROM.put(432, buf_slope[1]);
      EEPROM.commit();
      buffer_pointer = 40;
    }
  }
  while (buffer_pointer == 41) {
    int countdown = millis() - start_time;
    //    Serial.println("countdown: ");
    //    Serial.println(countdown, 2);
    //    Serial.println(countdown);
    phCalValue[3] = readCalpH();
    display_cal_timer(countdown);
    if (countdown  > 45000) {
      if (cal_mode == 2) {
        getCoeff(phCalValue, bufferValue, 31);
        getCoeff(phCalValue, bufferValue, 41);
        writeCoeffIntoEEPROM();
        buf_slope[2] = (((phCalValue[3] - phCalValue[2]) / (bufferValue[3] - bufferValue[2])) / 0.234) * 100;
        EEPROM.put(438, buf_slope[2]);
        EEPROM.commit();
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
    //    Serial.println(countdown, 2);
    //    Serial.println("countdown: ");
    //    Serial.println(countdown);
    phCalValue[4] = readCalpH();

    display_cal_timer(countdown);
    if (countdown  > 45000) {
      getCoeff(phCalValue, bufferValue, 41);
      buf_slope[3] = (((phCalValue[4] - phCalValue[3]) / (bufferValue[4] - bufferValue[3])) / 0.234) * 100;
      EEPROM.put(444, buf_slope[3]);
      EEPROM.commit();
      writeCoeffIntoEEPROM();
      buffer_pointer = 0;
      manual_cal_mode = 0;
      delay(50);
      probe_manual();
    }
  }
}
void manual_calibration() {
  //  Serial.println("log_mode");
  //  Serial.println(log_mode);
  //  if (log_mode == 0) {
  Serial.println("*************************************************enter manual_calibration********************************************************");
  while (manual_cal_mode == 1) {
    buffer_mov();
    buffer_page();
    timer_page();
    Serial.println(".................................");
    Serial.println(count);
    Serial.println(".................................");
    Serial.println(add_val1);
    Serial.println(".................................");
    Serial.println(add_val2);
    Serial.println(".................................");
    Serial.println(add_val3);
    Serial.println(".................................");
    Serial.println("LOOP MANUAL CALIBRATION");
    Serial.println("*************************************************EXIT manual_calibration********************************************************");
  }
  //  }
}
void probe_manual() {
  x3 = offset();
  //  if (WIFI_FLAG == 1) //Firebase.setFloat(firebaseData, "/PHMETER/EPT2006/Data/OFFSET", x3);
  delay(100);
  slope_total = slope();
  //  if (WIFI_FLAG == 1)// Firebase.setFloat(firebaseData, "/PHMETER/EPT2006/Data/SLOPE", slope_total);
  delay(100);
  EEPROM.put(420, slope_total);
  EEPROM.commit();
}
