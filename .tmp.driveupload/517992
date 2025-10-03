
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "globalVar.h"
#include <WiFi.h>
#include "Display.h"
// #include <EEPROM.h>
#include "EEPROM1.h"
#include <HTTPClient.h>
#include <WebServer.h>
#include "socket.h"
#include "adc.h"
#include "phSensor.h"
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <Update.h>
#include "OTA.h"
//#include "wifi_manager.h"
#include "values.h"
#include "manual.h"
#include "calibration.h"
volatile int buttonState = 0;
//volatile int log_button_flag = 0; // Flag to indicate button press
volatile unsigned long lastLogTime = 0; // Stores the last time data_sender was called
const unsigned long logInterval = 1000; // Interval in milliseconds (1 second)

void side_button_init() {
  pinMode(19, INPUT); // Set the pin as input
  pinMode(14, INPUT); // Set the pin as input
  pinMode(4, INPUT); // Set the pin as input
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(15, INPUT);
  pinMode(34, INPUT_PULLDOWN);
  pinMode(18, OUTPUT);
  pinMode(19, INPUT); // Set the pin as input
  OTA_BUTTON = digitalRead(14);
  delay(250);
  OTA_BUTTON = digitalRead(14);
  digitalWrite(18, LOW);
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
}
void IRAM_ATTR isr() {
  if (manual_cal_mode == 0) {
    log_button_flag = 1;
  }
}
void isr_routines() {
  //  pinMode(switchPin, INPUT_PtULLUP);
  //  attachInterrupt(digitalPinToInterrupt(switchPin), switchISR, CHANGE);
  // Initialize other variables or setup needed  //
  attachInterrupt(digitalPinToInterrupt(14), isr, FALLING);  //
  //  attachInterrupt(digitalPinToInterrupt(13), isr2, CHANGE);  // Probe Health Interrupt
  //  attachInterrupt(digitalPinToInterrupt(15), isr3, CHANGE);  // Calibration Mode Interrupt
}


void ota_init() {
  setup_ota_server();
  ota_server.begin();
}

void button_check() {
  int ok = digitalRead(14);
  int up = digitalRead(19);
  int dn = digitalRead(4);
  //  if (ok == 1) {
  //    probe_options_flag = 0;
  //    if (manual_cal_mode == 0) {
  //      Serial.println("entered isr OK Buuton");
  //      log_button_flag = 1;
  //    }
  //  }
  if (up == 1) {
    if (manual_cal_mode == 0) {
      Serial.println("entered isr2 UP Buuton");
      if (probe_options_flag == 1) {
        probe_options_flag = 0;
      }
      else if (probe_options_flag == 0) {
        probe_options_flag = 1;
      }
      buz_flag = 1;
    }
  }
  if (dn == 1) {
    probe_options_flag = 0;
    if (manual_calibration_flag == 1) {
      manual_cal_mode = 1;
      buz_flag = 1;

    }
  }
}


void probe_options() {
  if (probe_options_flag == 1) {
    probe_display();
    counter = counter + 1;
    if (counter > 5000) {
      probe_options_flag = 0;
    }
  }
}


void pH_main() {
  Serial.println("log_mode");
  Serial.println(log_mode);
  if (log_mode == 0 || log_mode == 1 || log_mode == 2) displays();
  else if (log_mode == 3) /*log_mode_disp();*/displays(); manual_cal_mode = 0;
  pH_read = pH_update();
  if (log_button_flag == 1) log_button();
  hold();
  Serial.println(" ph main ");
  Serial.println("pH_read=" + String(pH_read));
  room_temp();
  mV_update();
}

void EEPROM_reader()
{
  read_buffer_EEPROM();
  read_phcal_EEPROM();
  readCoeffFromEEPROM();
}


void log_button() {
  if (log_mode == 3) {
    if (delayflag == 1) {
      data_sender("LOG", String(1));
      buz_flag = 1;
      delayflag = 0;
    }
  }
  log_button_flag = 0;
}





//void isr_routines() {
//  digitalRead(4);
//  if (digitalRead(4) == 1) {
//    Serial.println("entered isr3");
//    manual_cal_mode = 1;
//  }
//}










void jason_send() {
  String runningdisp;
  jsonDoc["TIMER_RESET"] = "1";
  serializeJson(jsonDoc, runningdisp);
  Serial2.println(runningdisp);
}



void ota_check() {
  if (WIFI_FLAG == 1) ota_server.handleClient();
}

void setup()
{
  pinMode(23, OUTPUT);
  power_on_flag = 0;
  digitalWrite(23, HIGH);
  Serial.begin(115200);
  //  mySerial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  EEPROM.begin(700);
  delay(1000);
  digitalWrite(23, LOW);
  side_button_init();                        // Activate side buttons
  display_init();                          // Initialize OLED I2C
  delay(300);
  if (OTA_BUTTON == 1) {
    ota_init();                              // OTA Server Initialization
    pinMode(36, OUTPUT);

  } else {
    wifi_socket();
    ads_config();                              // External ADC Initialization
    EEPROM_reader();                           // Receive values saved in EEPROM
    //wifi();                                  // Setup Wi-Fi from EEPROM and trigger flags (WiFi, Firebase)
    pH_update();                               // pH Sensor Initialization
    read_slopes();
    room_temp();                             // Temperature Sensor Initialization
    mV_update();                             // mV Value Initialization
    isr_routines();                          // Interrupt Routines for button calls
  }
  power_on_flag = 1;
}
//   gp 28


void loop(void)
{
  if (OTA_BUTTON == 1) {
    buz_flag = 1;
    OTA_DISP();
    digitalWrite(36, HIGH);
    ota_server.handleClient();
    delay(300);
  }
  else {
    if (loop_int % 3 == 0) websockets.loop();
    else {
      currentMillis = millis();
      currentMillis_pH = millis();
      if (start_ph_cal == 0) {
        cal_button_check();                     // Calibration Button Check
        manual_calibration();                   // Button Calibration
        pH_main();                                // Tab Calibration/pH-Temp-mV-Battery Reading Mode
        probe_options();                          // Probe Display Screen
        button_check();
        buzzer();
        Serial2_read();
      }
      else if (start_ph_cal == 1) {
        phCalRoutine();
        cal_curve();
        cal_data();
        buzzer();
        Serial2_read();
      }
    }
    loop_int++;
  }
}
