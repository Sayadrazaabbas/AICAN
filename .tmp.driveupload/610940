#include "source.h"
long interval = 120000;
void IRAM_ATTR isr() {
  if (manual_cal_mode == 0) {
    Serial.println("entered isr");
    log_button_flag = 1;
  }
}
void IRAM_ATTR isr2() {
  if (manual_cal_mode == 0) {
    Serial.println("entered isr2");
    probe_options_flag = 1;
  }
}
void IRAM_ATTR isr3() {
  if (manual_calibration_flag == 1 && manual_cal_mode == 0) {
    Serial.println("entered isr3");
    manual_cal_mode = 1;
  }
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(600);
  ads_config();        // External ADC Initialization
  display_init();      // Initialize OLED I2C
  side_button_init();  // Activate side buttons
  EEPROM_reader();     // Receive values saved in EEPROM
  Serial.println("void setup entered_2");
  wifi();  // Setup Wi-Fi from EEPROM and trigger flags (WiFi, Firebase)
  Serial.println("void setup entered_3");
  mqtt_setup();
  pH_update();     // pH Sensor Initialization
  room_temp();     // Temperature Sensor Initialization
  mV_update();     // mV Value Initialization
  displays();      // OLED Display UI Initialization
  ota_init();      // OTA Server Initialization
  battery();       // Battery Indicator Function (Called once to avoid buffer overflow)
  isr_routines();  // Interrupt Routines for button calls
  topic_generator(did);
  Subscriptions();
  client.publish(RESET.c_str(), "1");
  client.publish("/meter/id", did.c_str());
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  currentMillis = millis();
  currentMillis_pH = millis();
  if (start_ph_cal == 0) {
    if (millis() - relayinit_timer > 1200000) {
      low_battery_trigger();  // 25% detect-trigger relay-start timer
      charging_cycle();       // 20-min charging
    }


    wifi_check();  // Check Wi-Fi status for Firebase
    //    firebase_check();                         // Firebase connection if setup() call fails
    ota_check();           // Keeps OTA Server Active
    led();                 // Indicator LEDs for power and Wi-Fi
    cal_button_check();    // Calibration Button Check
    manual_calibration();  // Button Calibration
    pH_main();             // Tab Calibration/pH-Temp-mV-Battery Reading Mode
    probe_options();       // Probe Display Screen
    //   Serial.println(did);
  }

  while (start_ph_cal == 1) {
    client.loop();
    // cal_disp();
    phCalRoutine();
    cal_curve();
    cal_data();
  }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////FUNCTIONS///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void isr_routines() {
  attachInterrupt(digitalPinToInterrupt(14), isr, HIGH);   // Manual Log Interrupt
  attachInterrupt(digitalPinToInterrupt(13), isr2, HIGH);  // Probe Health Interrupt
  attachInterrupt(digitalPinToInterrupt(15), isr3, HIGH);  // Calibration Mode Interrupt
}

void probe_options() {
  if (probe_options_flag == 1) {
    probe_display();
    //delay(10000);
    probe_options_flag = 0;
  }
}

void ota_init() {
  setup_ota_server();
  ota_server.begin();
}

void wifi() {
  Serial.print("Reading Wifi EEPROM");
  read_wifi_eeprom();
  check_wifi_config();
  Serial.print("Cheking Wifi Configuration");
  connect_wifi();
  Serial.print("connecting To Wifi");
  setup_wifi_check();
}




void EEPROM_reader() {
  Serial.print("reading EEprom Value ");
  read_buffer_EEPROM();
  read_phcal_EEPROM();
  readCoeffFromEEPROM();
  read_slopes();
  read_ip_did();
}




void setup_wifi_check() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connection Status Positive");
    digitalWrite(26, HIGH);
    WIFI_FLAG = 1;
    fb_init = 1;
    //    firebase_initialization();
  } else {
    Serial.println("Wi-Fi Not Connected");
    WIFI_FLAG = 0;
  }
}




void side_button_init() {
  Serial.print("Initializing Pins ");
  Serial.println("wifi blue led pin 26");
  Serial.println("power red led = 23");
  Serial.println("relay pin  = 18");
  Serial.println("WIFI BUTTON  = 14");
  pinMode(26, OUTPUT);  // wifi blue led
  pinMode(23, OUTPUT);  // power red led
  pinMode(18, OUTPUT);  // relay
  pinMode(14, INPUT);   // wifi button
  Serial.print("Turning On Power Led ");
  digitalWrite(18, LOW);
  digitalWrite(23, HIGH);
  digitalWrite(26, LOW);
  relayinit_timer = millis();
}






void pH_main() {
  if (log_mode == 0) displays();
  else if (log_mode == 1) {
    log_mode_disp();
    log_button();
  }
  pH_read = pH_update();
  //  hold();
  room_temp();
  mV_update();
  if (currentMillis - previous > interval) {
    previous = currentMillis;  ////////////////////////////////////////////////////////////////////////////////
    battery();
  }
}





void wifi_check() {
  if (WiFi.status() != WL_CONNECTED) {
    WIFI_FLAG = 0;
    fb_count = 0;
  } else {
    WIFI_FLAG = 1;
    fb_count + 1;
  }
}





void ota_check() {
  if (WIFI_FLAG == 1) ota_server.handleClient();
}




void led() {
  if (WiFi.status() != WL_CONNECTED) digitalWrite(26, LOW);
  else digitalWrite(26, HIGH);
}




void log_button() {
  if (log_button_flag == 1) {
    client.publish(LOG.c_str(), "1");
    Serial.println("Wi-Fi button pressed for log");
    //    if (WIFI_FLAG == 1) {
    //    Serial.println("Firebase triggered");
    //    Firebase.setInt(firebaseData, "/PHMETER/EPT2021/Data/LOG", 1);
    //*************************************************************//
    //    }
  }
  log_button_flag = 0;
}






void low_battery_trigger() {
  if (y < 25 && relay_test == 0) {
    relay_test = 1;
    digitalWrite(18, LOW);
    starter = millis();
    battery_warning();
  }
}




void charging_cycle() {
  if (starter != 0 && millis() > (starter + 1200000)) {
    digitalWrite(18, HIGH);
    relay_test = 0;
    starter = 0;
  }
}
