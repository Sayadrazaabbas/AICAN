// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SH1106.h>
// #include <Fonts/FreeSansBold9pt7b.h>
// #include <Fonts/FreeSans9pt7b.h>
// #include <Fonts/FreeSans12pt7b.h>
// #include <Fonts/FreeMonoBold9pt7b.h>
// #include <Fonts/Picopixel.h>
// Adafruit_SH1106 display(21, 22);
// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
//int tdr;
int mv;
int t;
///////////////////////////      1      ///////////////////////////////////////
void display_init() {
  runningdisp = " ";
  //  String runningdisp;
  jsonDoc["status"] = "1";
  // Serialize JSON to a string
  serializeJson(jsonDoc, runningdisp);
  // Send JSON string to RP2040
  //  Serial2.println(runningdisp);
  Serial.println(runningdisp);
  // display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  // display.clearDisplay();
  // display.setTextSize(2);
  // display.setTextColor(WHITE);
  // display.setCursor(30, 15);
  // display.print("VENUS");
  // display.setCursor(35, 45);
  // display.print("LABS");
  // display.display();
  buzzer();
  sender();
}
///////////////////////////     1    ///////////////////////////////////////






///////////////////////////    2    ///////////////////////////////////////
void displays() {
  if (probe_options_flag == 0) {
    buzzer();
//    delaysender();
    runningdisp = " ";
    //  String runningdisp;
    jsonDoc["status"] = "2";
    jsonDoc["log_mode"] = log_mode;
    //    tdr = random(0, 13);
    //    mv = random(-400, 400);
    //    t = random(25, 50);
    // display.clearDisplay();
    // // display.drawLine(0, 15, display.width() - 3, 15, WHITE);
    // display.drawLine(85, 15, 85, 0, WHITE);
    // display.drawLine(35, 15, 35, 0, WHITE);
    //display.fillRect(1, 21, 126, 42, BLACK);
    // display.setFont();
    // display.setTextSize(1);
    // display.setTextColor(WHITE);
    // display.setCursor(0, 5);
    // char str8[10];
    // sprintf(str8, "%d", y);
    // display.print(str8);
    // display.print(" %");
    // display.setCursor(40, 5);
    // char str2[10];
    //  if(vals == -127)  {display.setCursor(45, 5); display.print("NA");}
    //  else {
    // sprintf(str2, "%.1f", vals);
    // display.print(str2);
    // display.print(" C");
    //  jsonDoc["temp_val"] = str2;
    jsonDoc["temp_val"] = tdr;
    // display.setFont();
    // display.setTextSize(1);
    // display.setTextColor(WHITE);
    // display.setCursor(90, 5);
    int z = mVx;
    char str3[10];
    sprintf(str3, "%d", z);
    // display.print(str3);
    jsonDoc["mv_val"] = str3;
    // display.print("mV");
    // display.setFont();
    // display.setTextSize(1);
    // display.setTextColor(WHITE);
    // display.setCursor(50, 20);
    // display.print("pH:");
    // display.setCursor(110, 20);
    if (hodl == 1) /*display.print("ST"); */jsonDoc["hold"] = hodl;
    // display.setTextSize(2);
    // display.setTextColor(WHITE);
    // display.setFont(&FreeSans9pt7b);
    // display.setCursor(5, 55);


    total1 = total1 - readings1[readIndex1];
    // read from the sensor:
    readings1[readIndex1] = x;
    // add the reading to the total:
    total1 = total1 + readings1[readIndex1];
    // advance to the next position in the array:
    readIndex1 = readIndex1 + 1;

    // if we're at the end of the array...
    if (readIndex1 >= numReadings1) {
      // ...wrap around to the beginning:
      readIndex1 = 0;
    }
    // calculate the average:
    average1 = total1 / numReadings1;
    PH_val = average1;
    char str[10];
    sprintf(str, "%.2f", PH_val);
    // display.print(str);
    jsonDoc["main_val"] = PH_val;
    //  jsonDoc["main_val"] = tdr;
    //  Serial.print("display_ph:");
    //  Serial.print(str);
    // display.display();
    serializeJson(jsonDoc, runningdisp);
    sender();
  }
}
///////////////////////////       2      ///////////////////////////////////////








///////////////////////////     3    ///////////////////////////////////////
void cal_disp(float d) {
  buzzer();
  runningdisp = " ";
  //  Serial.println("Status 3");
  //  String runningdisp;
  jsonDoc["status"] = "3";
  //  Serial.println("enter cal_disp");
  jsonDoc["cal_button"] = calButton;
  // display.clearDisplay();
  // display.setTextSize(1);
  // display.setCursor(14, 20);
  // display.print("Calibrating");
  //  Serial.println("Calibrating");
  // display.setCursor(25, 50);
  // display.print(d);
  jsonDoc["CAL_VAL"] = d;
  //  Serial.println("CAL_VAL: " + String(d));
  // display.display();
  serializeJson(jsonDoc, runningdisp);
  //  Serial2.println(runningdisp);
  //  Serial.println(runningdisp);
  sender();

}
///////////////////////////    3    ///////////////////////////////////////







///////////////////////////    4    ///////////////////////////////////////
void battery_warning() {
  buzzer();
  runningdisp = " ";
  jsonDoc["status"] = 4;
  //  String runningdisp;
  // display.clearDisplay();
  // display.setTextSize(1);
  // display.setCursor(14, 30);
  // display.print("BATTERY");
  // display.setCursor(24, 40);
  // display.print("LOW");
  // display.display();
  serializeJson(jsonDoc, runningdisp);
  // Send JSON string to RP2040
  //  Serial2.println(runningdisp);
  //  Serial.println(runningdisp);
  sender();

}
///////////////////////////    4   ///////////////////////////////////////







///////////////////////////    5    ///////////////////////////////////////
void cal_home() {
  buzzer();
  runningdisp = " ";
  jsonDoc["status"] = 5;
  //  Serial.println("Status 5");
  //  String runningdisp;
  // display.clearDisplay();
  // display.setFont();
  // display.setTextSize(1);
  // display.setCursor(35, 5);
  // display.print("CALIBRATION");
  //  Serial.println("CALIBRATION");
  // display.setCursor(60, 15);
  // display.print("MODE");
  // //  Serial.println("MODE");
  // display.setCursor(20, 50);
  // display.print("Press to Start");
  //  Serial.println("Press to Start");
  // display.display();
  // serializeJson(jsonDoc, runningdisp);
  // Send JSON string to RP2040
  //  Serial2.println(runningdisp);
  //  Serial.println(runningdisp);
  //  delay(500);
  sender();
}
///////////////////////////    5  ///////////////////////////////////////






///////////////////////////    6  ///////////////////////////////////////
void display_cal_timer(int y) {
  buzzer();
  runningdisp = " ";
  //  String runningdisp;
  //  Serial.println("Status 6");
  jsonDoc["status"] = 6;
  // display.clearDisplay();
  // display.drawLine(0, 20, display.width() - 3, 20, WHITE);
  // display.setFont();
  // display.setTextSize(1);
  // display.setCursor(0, 0);
  // display.print("Keep pH probe dipped");
  //  Serial.println("Keep pH probe dipped");
  // display.setCursor(0, 9);
  // display.print("till timer ends");
  //  Serial.println("till timer ends");
  // display.setCursor(5, 22);
  // display.print("Seconds Remaining:");
  //  Serial.println("Seconds Remaining:");
  // display.setFont(&FreeSans9pt7b);
  // display.setCursor(15, 20);
  // display.print("CAL TIMER:");
  //  Serial.print("CAL TIMER-:");
  // display.setFont(&FreeSans9pt7b);
  // display.setTextSize(2);
  char string[10];
  y = 45 - (y / 1000);
  if (y > 0) sprintf(string, "%d", y);
  // display.setCursor(15, 60);
  //  Serial.println(string);
  // display.print(string);
  // display.display();
  jsonDoc["cal_timer"] = string ;
  jsonDoc["cal_time"] = y;
  serializeJson(jsonDoc, runningdisp);
  //  Serial2.println(runningdisp);
  //  Serial.println(runningdisp);
  //  delay(200);
  sender();

}
///////////////////////////    6  ///////////////////////////////////////






///////////////////////////    7  ///////////////////////////////////////
void buf_run(int c, float y) {
  buzzer();
  runningdisp = " ";
  //  String runningdisp;
  jsonDoc["status"] = "7";
  //  Serial.println("Status 7");
  // display.clearDisplay();
  // display.drawLine(0, 20, display.width() - 3, 20, WHITE);
  // display.setFont();
  // display.setTextSize(1);
  // display.setCursor(0, 0);
  // display.print("Press OK to change");
  // //  Serial.println("Press OK to change");
  // display.setCursor(0, 9);
  // display.print("buffer value");
  // //  Serial.println("buffer value");
  // display.setCursor(15, 25);
  // display.print("SELECT BUFFER");
  // //  Serial.println("SELECT BUFFER");
  // display.print(c);
  // //  Serial.print("C :" + String(c));
  jsonDoc["c"] = c;
  // display.print(":");
  // display.setTextSize(2);
  // display.setTextColor(WHITE);
  // display.setFont(&FreeSans9pt7b);
  // display.setCursor(15, 60);
  float xyz = y;
  char string[10];
  sprintf(string, "%.2f", xyz);
  // display.print(string);
  //  Serial.println("y =");
  //  Serial.print(string);
  // display.display();
  jsonDoc["BUFFER_VAL"] = string;
  serializeJson(jsonDoc, runningdisp);
  //  Serial2.println(runningdisp);
  //  Serial.println(runningdisp);
  //  delay(500);
  sender();
}
///////////////////////////      7   ///////////////////////////////////////





/////////////////////////////////////////  8  //////////////////////////////////////////////
void runner_val(int c, float y) {
  runningdisp = " ";
  buzzer();
  //  String runningdisp;
  jsonDoc["status"] = "8";
  //  Serial.println("Status 8");
  // display.clearDisplay();
  // display.drawLine(0, 20, display.width() - 3, 20, WHITE);
  // display.setFont();
  // display.setTextSize(1);
  // display.setCursor(0, 0);
  // display.print("Press arrow keys to");
  //  Serial.println("Press arrow keys to");
  // display.setCursor(0, 9);
  // display.print("move value");
  // //  Serial.println("move value");
  // display.setCursor(15, 25);
  // display.print("SELECT BUFFER");
  //  Serial.println("SELECT BUFFER");
  // display.print(c);
  //  Serial.println(c);
  jsonDoc["c"] = c;
  // display.print(":");
  // display.setTextSize(2);
  // display.setTextColor(WHITE);
  // display.setFont(&FreeSans9pt7b);
  // display.setCursor(15, 60);
  float xyz = y;
  char string[10];
  sprintf(string, "%.2f", xyz);
  // display.print(string);
  //  Serial.println(string);
  // display.display();
  jsonDoc["runner_val"] = string;
  serializeJson(jsonDoc, runningdisp);
  //  Serial2.println(runningdisp);
  //  Serial.println(runningdisp);
  //  delay(500);
  sender();
}
//////////////////////////////////////    8    /////////////////////////////////////////////////





///////////////////////////    9     ///////////////////////////////////////
//void log_mode_disp() {
//  buzzer();
//  runningdisp = " ";
//  //  jsonDoc["status"] = "9";
//  jsonDoc["log"] = "1";
//  //  Serial.println("Status 9");
//  display.clearDisplay();
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.setCursor(5, 15);
//  display.print("BUTTON LOG");
//  display.setCursor(20, 45);
//  display.print("MODE ON");
//  display.display();
//  //  String runningdisp;
//  serializeJson(jsonDoc, runningdisp);
//  // Send JSON string to RP2040
//  //  Serial2.println(runningdisp);
//  //  Serial.println(runningdisp);
//  sender();
//}
///////////////////////////    9   ///////////////////////////////////////





///////////////////////////    10  ///////////////////////////////////////
void logman_disp() {
  buzzer();
  runningdisp = " ";
  jsonDoc["status"] = "10";
  //  String runningdisp;
  //  Serial.println("Status 10");
  // display.clearDisplay();
  // display.setFont();
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(30, 15);
  // display.print("MEMORY");
  // display.setCursor(35, 30);
  // display.print("FULL");
  // display.setCursor(10, 50);
  // display.print("Do you want to continue?");
  // display.display();
  serializeJson(jsonDoc, runningdisp);
  //  Serial2.println(runningdisp);
  //  Serial.println(runningdisp);
  sender();

}
///////////////////////////    10   ///////////////////////////////////////





///////////////////////////    11  ///////////////////////////////////////
void OTA_DISP() {
  //  String runningdisp;
  buzzer();
  runningdisp = " ";
  jsonDoc["status"] = "11";
  //  Serial.println("Status 11");
  // display.clearDisplay();
  // display.setTextSize(2);
  // display.setTextColor(WHITE);
  // display.setCursor(45, 15);
  // display.print("IP ");
  // display.setTextSize(1);
  // display.setCursor(20, 45);
  // display.print(WiFi.localIP());
  //  String ip =  WiFi.localIP().toString();
  jsonDoc["IP"] = WiFi.localIP();
  // display.display();
  serializeJson(jsonDoc, runningdisp);
  //  Serial2.println(runningdisp);
  //  Serial.println(runningdisp);
  //  delay(300);
  sender();
}
///////////////////////////    11  ///////////////////////////////////////







///////////////////////////////    12  ////////////////////////////////
void probe_display() {
  jsonDoc["status"] = "12";
  buzzer();
  runningdisp = " ";
  //  String runningdisp;
  //  display.clearDisplay();
  //  display.setFont();
  //  display.setTextSize(1);
  //  display.setTextColor(WHITE);
  //  display.setCursor(25,0);
  //  display.print("PROBE HEALTH");
  //  display.setCursor(0,20);
  //  display.print("Average Slope: ");
  //  char stringA[10], slopeA[10], slopeB[10], slopeC[10], slopeD[10];
  jsonDoc["slope1"] = buf_slope[0];
  jsonDoc["slope2"] = buf_slope[1];
  jsonDoc["slope3"] = buf_slope[2];
  jsonDoc["slope4"] = buf_slope[3];
  jsonDoc["slope_main"] = slope_total;
  //  sprintf(stringA, "%.1f", slope_total);
  //  sprintf(slopeA, "%.1f", buf_slope[0]);
  //  sprintf(slopeB, "%.1f", buf_slope[1]);
  //  sprintf(slopeC, "%.1f", buf_slope[2]);
  //  sprintf(slopeD, "%.1f", buf_slope[3]);
  //  display.print(stringA);
  //  display.setCursor(0,30);
  //  display.print("S1: ");
  //  display.print(buf_slope[0]);
  //  display.setCursor(60,30);
  //  display.print("S2: ");
  //  display.print(buf_slope[1]);
  //  display.setCursor(0,40);
  //  display.print("S3: ");
  //  display.print(buf_slope[2]);
  //  display.setCursor(60,40);
  //  display.print("S4: ");
  //  display.print(buf_slope[3]);
  //    display.setCursor(0,50);
  //    display.print("Offset: ");
  char stringB[10];
  sprintf(stringB, "%.2f", x3);
  // display.print(stringB);
  jsonDoc["offset"] = stringB;
  //  display.display();
  serializeJson(jsonDoc, runningdisp);
  Serial2.println(runningdisp);
  //  Serial.println(runningdisp);
  sender();

}
////////////////////////////////   12   ////////////////////////////////////////
