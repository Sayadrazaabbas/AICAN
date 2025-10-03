unsigned long time_now = 0; // Initialize a variable to store the current time
unsigned long time1 = 0; // Initialize a variable to store the current time
int raw;
const int RX_PIN = 16; // Connect this to the TX pin of the other device
const int TX_PIN = 17;
StaticJsonDocument<1024> jsonDoc;
const unsigned long DEBOUNCE_DELAY = 50; // Debounce delay in milliseconds
const unsigned long LONG_PRESS_DURATION = 2000; // Long press duration in milliseconds
int tdr = random(0, 100);
int buz_flag = 0;
unsigned long lastButtonPressTime = 0;
// #include <FirebaseESP32.h>
float ip = 0;
int OTA_BUTTON = 0;
// Values
long previous = 0;                  // timer variable for battery reading interval
unsigned long currentMillis;        // timer variable for battery reading interval
boolean hodl = 0;                    // stable pH value final
float x = 0;                            // pH value final
int y = 0;                             // battery value final
float mVx;                          // mV value final
float vals;                         // temp. value final

int loop_int = 0;
// Wifi & Firebase Checks
boolean fb_count = 0;
boolean fb_init = 0;
float R_C = 38;
int SENSORSELECT = 0;//by def 0 means NTC TEMPRATURE SENSOR
boolean WIFI_FLAG = 0;              // WiFi Flag Main

int start_ph_cal = 0;
int start_ec_cal = 0;
float slope_total = 0;
float buf_slope[4] = {0, 0, 0, 0};

float bufferValue[5] = {1, 4, 7, 9.2, 12};
float atcbufferValue[5] = {1, 4, 7, 9.2, 12};
float phCalValue[5] = {0.18, 0.94, 1.68, 2.28, 3.11};
float phCalCoeff[9] = {0.00, 0.42, -0.36, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
float ATCCalCoeff[9] = {0.00, 0.42, -0.36, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};

int calButton = 0;     // Calibration Variable
int cal_mode = 0;      // Cal Mode 3/5 point
int atc_var = 0;       // ATC mode on/off
int fb_flag = 0;       // Flag for after cal firebase hits
float post1, post2, post3, post4, post5;   // Post Cal pH value hits

// FirebaseData firebaseData;
// FirebaseData fbdo1;

unsigned long currentMillis_pH;     // 3 second timer for pH stability comparison
unsigned long previous_pH;          // 3 second timer for pH stability comparison

float x_prev;                       // pH (t-3 seconds)
float pH_read;                      // pH (t seconds)

float c1, c2, c3, c4, c5;           // compensated pH for mV calculation (calibration)

//Manual Calibration
int buffer_pointer = 0;
boolean manual_cal_mode = 0;
boolean change_buffer = 0;
boolean delayflag = 0;
float add_val1, add_val2, add_val3, add_val4, add_val5;
float bufferValue3[3] = {4, 7, 9.2};
float atcbufferValue3[3] = {1, 4, 7};
float phCalValue3[3] = {0.18, 0.94, 1.68};
float phCalCoeff3[4] = {0.00, 0.42, -0.36, 0.00};
float ATCCalCoeff3[4] = {0.00, 0.42, -0.36, 0.000};

//min-max table feature
float log_mode = 0;
float minMV[5] = {0, 0, 0, 0, 0};
float maxMV[5] = {0, 0, 0, 0, 0};
float  increment = 0.01;
int manual_calibration_flag = 0;
float manual_atc = 0;               // On-demand ATC

//TEST VARIABLE
long int starter = 0;               // Battery Charging Cycle Timer Start
int relay_test = 0;                 // Charger relay value
int Ro = 10;                        // Temp. sensor resistor value
float x3;                           // offset variable
boolean  log_button_flag = 0;       // button log flag variable
int H_BUTTON = 0;
unsigned int power_on_flag = 0;
unsigned int mute_flag = 1;
int smoothed_temp_val = 25;
//float temp_vals = 0;
float PH_val = 0.00;
int probe_options_flag = 0;



//EEPROM.put(698, mute_flag);
void buzzer() {
  if (buz_flag == 1) {
    digitalWrite(23, HIGH);
    time_now = millis();
    if (time_now >= 800) {
      Serial.println("LOW");
      delay(50);
      digitalWrite(23, LOW);
      time_now = millis();
      buz_flag = 0;
    }
  } else if (buz_flag == 2) {
    digitalWrite(23, HIGH);
    delay(1000);
    digitalWrite(23, LOW);
  }
}



void Serial2_read() {
  if (Serial2.available() > 0) {
    Serial2.setTimeout(200);
    String jsonString = Serial2.readString();
    // Parse the JSON string
    StaticJsonDocument<1024> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, jsonString);
    if (error) {
      Serial.println("Failed to parse JSON");
    } else {
      buz_flag = jsonDoc["BUZZER"];
      smoothed_temp_val = jsonDoc["SMT"];
    }
  }
}

unsigned long conts = 0;        // will store last time LED was updated
String runningdisp = " ";
void sender() {
  unsigned long currentMillis = millis();
  if (currentMillis - conts >= 500) {
    Serial2.println(runningdisp);
    Serial.println(runningdisp);
    conts = currentMillis;
    delayflag = 1;
  }
}




//unsigned long delayconts = 0;        // will store last time LED was updated
//void delaysender() {
//  unsigned long delaycurrentMillis = millis();
//  if (delaycurrentMillis - delayconts >= 10000) {
//    delayconts = delaycurrentMillis;
//    delayflag = 1;
//  }
//}



int first_run_flag = 0;

float temp_vals  = 0.00;
const int numReadings = 10;
float readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
float total = 0.0;                  // the running total
float average = 0.0;                // the average


int counter = 0;

float temp_vals1  = 0.00;
const int numReadings1 = 10;
float readings1[numReadings1];      // the readings from the analog input
int readIndex1 = 0;              // the index of the current reading
float total1 = 0.0;                  // the running total
float average1 = 0.0;                // the
