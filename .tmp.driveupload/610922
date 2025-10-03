//#include <FirebaseESP32.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#define PUBLISH_INTERVAL 5000
unsigned long lastPHPublish = 0;
unsigned long lastMVPublish = 0;
unsigned long lastTempPublish = 0;
unsigned long lastHOLDPublish = 0;




long previous = 0;                  // timer variable for battery reading interval
unsigned long currentMillis;        // timer variable for battery reading interval
boolean hodl = 0;                   // stable pH value final
float x;                            // pH value final
int y;                              // battery value final
float mVx;                          // mV value final
float vals;                         // temp. value final
float slope_total;                  // slope_main

int relayinit_timer = 0;
int manual_calibration_flag = 0;     // Manual calibration mode
// Wifi & Firebase Checks
boolean fb_count = 0;
boolean fb_init = 0;

boolean WIFI_FLAG = 0;              // WiFi Flag Main

int start_ph_cal = 0;
int start_ec_cal = 0;

// 5-POINT CALIBRATION
float bufferValue[10] = {1, 4, 7, 9.2, 12};
float ongoingbuffer = 0;
float atcbufferValue[5] = {1, 4, 7, 9.2, 12};
float phCalValue[5] = {0.18, 0.94, 1.68, 2.28, 3.11};
float phCalCoeff[9] = {0.00, 0.42, -0.36, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
float ATCCalCoeff[9] = {0.00, 0.42, -0.36, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};

// 3-POINT CALIBRATION
float bufferValue3[3] = {4, 7, 9.2};
float atcbufferValue3[3] = {1, 4, 7};
float phCalValue3[3] = {0.18, 0.94, 1.68};
float phCalCoeff3[4] = {0.00, 0.42, -0.36, 0.00};
float ATCCalCoeff3[4] = {0.00, 0.42, -0.36, 0.000};

float buf_slope[4] = {0, 0, 0, 0};
int calButton = 0;     // Calibration Variable
int cal_mode = 0;      // Cal Mode 3/5 point
int atc_var = 0;       // ATC mode on/off
int fb_flag = 0;       // Flag for after cal firebase hits
float post1, post2, post3, post4, post5;   // Post Cal pH value hits

//FirebaseData firebaseData;
//FirebaseData fbdo1;

unsigned long currentMillis_pH;     // 3 second timer for pH stability comparison
unsigned long previous_pH;          // 3 second timer for pH stability comparison

float x_prev;                       // pH (t-3 seconds)
float pH_read;                      // pH (t seconds)

float c1, c2, c3, c4, c5;           // compensated pH for mV calculation (calibration)

//Manual Calibration
int buffer_pointer = 0;
boolean manual_cal_mode = 0;
boolean change_buffer = 0;
float add_val1, add_val2, add_val3, add_val4, add_val5;

//min-max table feature
boolean log_mode = 0;
float minMV[5] = {0, 0, 0, 0, 0};
float maxMV[5] = {0, 0, 0, 0, 0};


float manual_atc = 0;               // On-demand ATC

//TEST VARIABLE
long int starter = 0;               // Battery Charging Cycle Timer Start
int relay_test = 0;                 // Charger relay value
int Ro = 0;                        // Temp. sensor resistor value
float x3;                           // offset variable
boolean  log_button_flag = 0;       // button log flag variable
boolean probe_options_flag = 0;
boolean cal_button_flag = 0;
int  MQTTY = 0;
/////////////////////////CHAR VARABLE FOR MQTT?////////////////////////////////////////


char Ph_val[10];
char Temp_val[10];
char Mv_val[10];
char Battery[10];
char Slope[10];
char Offset[10];

char mv_1[10];
char mv_2[10];
char mv_3[10];
char mv_4[10];
char mv_5[10];

char post_val_1[10];
char post_val_2[10];
char post_val_3[10];
char post_val_4[10];
char post_val_5[10];

char val_1[10];
char val_2[10];
char val_3[10];
char val_4[10];
char val_5[10];

char temp_val_1[10];
char temp_val_2[10];
char temp_val_3[10];
char temp_val_4[10];
char temp_val_5[10];


char slope_1[10];
char slope_2[10];
char slope_3[10];
char slope_4[10];
char slope_5[10];

char Hold[10];
char Log_interval[10];
char Log[10];
char Auto_log[10];

/////////////////////////CHAR VARABLE FOR MQTT////////////////////////////////////////
String ip;
String did;
String mid;
