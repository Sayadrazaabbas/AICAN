#include"Source.h"
#include <ArduinoJson.h>
#include <Arduino.h>
int LIMIT = 38;
UDOUBLE Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
UWORD *BlackImage;
unsigned long startTime;
const int ESP_POWER = 5;
const int powerswitch = 3 ;
const int ON_PIN = 27;
const int MOSFET_PIN = 20;
int sstatus = 0;
float smoothedValue = 0;





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const unsigned long interval = 1000; // Time interval in milliseconds (5 seconds)
unsigned long previousMillis = 0;   // Stores the last time the function was called
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void averaging() {
  reading[currentIndex] = sensorValue;
  currentIndex = (currentIndex + 1) % windowSize;

  float sum = 0.0;
  for (int i = 0; i < windowSize; i++) {
    sum += reading[i];
  }
  movingAvg = sum / windowSize;
  movingAvg = 25;
  String runningdisp;
  jsonDoc["SMT"] = movingAvg;
  serializeJson(jsonDoc, runningdisp);
  //  Serial1.println(runningdisp);
}



float calculateBatteryPercentage(float voltage, float minVoltage, float maxVoltage) {
  if (voltage < minVoltage) {
    voltage = minVoltage;
  } else if (voltage > maxVoltage) {
    voltage = maxVoltage;
  }
  // Calculate the percentage using linear interpolation
  float percentage = ((voltage - minVoltage) / (maxVoltage - minVoltage)) * 100.0;
  // Ensure the percentage is within the valid range (0% to 100%)
  if (percentage < 0.0) {
    percentage = 0.0;
  } else if (percentage > 100.0) {
    percentage = 100.0;
  }
  return percentage;
}
class MovingAverage {
  public:
    MovingAverage(int size) : size(size), values(new float[size]), index(0), sum(0) {
      for (int i = 0; i < size; ++i) {
        values[i] = 0.0;
      }
    }
    ~MovingAverage() {
      delete[] values;
    }
    float update(float newValue) {
      sum -= values[index];
      values[index] = newValue;
      sum += newValue;
      index = (index + 1) % size;
      return sum / size;
    }
  private:
    int size;
    float* values;
    int index;
    float sum;
};
MovingAverage movingAverage(200);



void battery() {

}
void setup() {
  //  ******************Averaging INIT ***********************
  for (int i = 0; i < windowSize; i++) {
    readings[i] = 0.0;
  }
  //  **********************************************************
  DEV_Module_Init();
  QMI8658_init();
  LCD_1IN28_Init(VERTICAL);
  DEV_SET_PWM(100);
  startTime = millis();
  BlackImage = (UWORD *)malloc(Imagesize);
  Paint_NewImage((UBYTE *)BlackImage, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, 0, WHITE);
  Paint_SetScale(65);
  Paint_SetRotate(ROTATE_270);
  Paint_DrawImage(template1, 0, 0, 240, 240);
  Paint_DrawString_EN(46, 65, ("CRESCENT"), &Font24, WHITE, WHITE);
  Paint_DrawString_EN(35, 95, ("SCIENTIFIC"), &Font24, WHITE, WHITE);
  Paint_DrawString_EN(55, 140, ("PH METER"), &Font24, WHITE, WHITE);
  Paint_DrawString_EN(111, 34, ("" + String(smoothedValue, .0f) + "%").c_str(), &Font16, WHITE, GREEN); // Battery Percentage
  LCD_1IN28_Display(BlackImage);
}






void loop() {
  QMI8658_read_xyz(acc, gyro, &tim_count);
  //  Serial.println("G1" + String(gyro[0])); Serial.println("G2" + String(gyro[1]));  Serial.println("G3" + String(gyro[2]));
  movement();
  if (average > LIMIT && sleep_flag == 0) {
    Paint_DrawImage(template1, 0, 0, 240, 240); // Draw image at (50, 50) with dimensions 240*240
    Paint_DrawString_EN(88, 65, ("OVER"), &Font24, WHITE, RED);
    Paint_DrawString_EN(50, 100, ("TEMRATURE"), &Font24, WHITE, RED);
    Paint_DrawString_EN(30, 140, ("PLEASE WAIT"), &Font24, WHITE, WHITE);
    Paint_DrawString_EN(148, 187, ("*c"), &Font12, WHITE, RED);
    Paint_DrawString_EN(95, 180, ("" + String(average, .0f)).c_str(), &Font48, WHITE, RED);
    Paint_DrawString_EN(111, 34, ("" + String(smoothedValue, .0f) + "%  ").c_str(), &Font16, WHITE, GREEN);
    LCD_1IN28_Display(BlackImage);
  }







  //  ***************************************                                    ********************************
  //  ***************************************                                    ********************************
  //  ***************************************    Serial Reand Handle And Decision********************************
  //  ***************************************                                    ********************************
  //  ***************************************                                    ********************************
  if (Serial1.available() > 0) {
    currentTime = 0;
    Serial1.setTimeout(200);
    String jsonString = Serial1.readString();
    delay(50);
    Serial.println("serial.Avilable");
    Serial.println(jsonString);
    Serial.println("serial.FINISH");

    // Parse the JSON string
    StaticJsonDocument<1024> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, jsonString);
    ////////////////////////////////////////////////////////////                                           ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////       Jason Data Reciving And Handling    /////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////                                            /////////////////////////////////////////////////////
    if (error) {
      Serial.println("Failed to parse JSON");
    } else if (!error)  {
      Serial.println("parse Sucsessfully JSON");
      status = jsonDoc["status"];
      int temp_val = jsonDoc["temp_val"];
      sensorValue  = jsonDoc["temp_vals"];
      int log_mode = jsonDoc["log_mode"];
      int mv_val = jsonDoc["mv_val"];
      int hold = jsonDoc["hold"];
      int slope1 = jsonDoc["slope1"];
      int slope2 = jsonDoc["slope2"];
      int slope3 = jsonDoc["slope3"];
      int slope4 = jsonDoc["slope4"];
      int slope_main = jsonDoc["slope_main"];
      int offset = jsonDoc["offset"];
      float main_val = jsonDoc["main_val"];
      int c = jsonDoc["c"];
      float cal_mode = jsonDoc["cal_mode"];
      float bufferValue = jsonDoc["bufferValue"];
      float CAL_TIMER = jsonDoc["cal_timer"];
      float  CAL_TIME = jsonDoc["cal_time"];
      float runner_val = jsonDoc["runner_val"];
      String IP = jsonDoc["IP"];
      float  BUFFER_VAL = jsonDoc["BUFFER_VAL"];
      float  CAL_VAL = jsonDoc["CAL_VAL"];
      int button_esp = jsonDoc["button_pressed"];
      if (button_esp == 1 || button_esp == 2 || button_esp == 3)reset_flag = 1;
      button_esp = 0;
      jsonString = "";
      temp_val = movingAvg;
      if (status < 0 || status == 0)status = 2;
      ////////////////////////////////////////////////////////////                                           ////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////        Jason   Data   Reciving   DONE    /////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////                                            /////////////////////////////////////////////////////


      /////////////////////////////////////////////  STATUS == 1   ///////////////////////////////////////////////////////
      if (status == 1) {
        Paint_DrawImage(template1, 0, 0, 240, 240); // Draw image at (50, 50) with dimensions 240*240
        Paint_DrawString_EN(46, 65, ("CRESCENT"), &Font24, WHITE, WHITE);
        Paint_DrawString_EN(35, 95, ("SCIENTIFIC"), &Font24, WHITE, WHITE);
        Paint_DrawString_EN(55, 140, ("PH METER"), &Font24, WHITE, WHITE);
        Paint_DrawString_EN(111, 34, ("" + String(smoothedValue, .0f) + "%").c_str(), &Font16, WHITE, GREEN);
      }
      /////////////////////////////////////////////  STATUS == 1   ///////////////////////////////////////////////////////



      /////////////////////////////////////////////  STATUS == 2   ///////////////////////////////////////////////////////
      else if (status == 2 || status == 9) {
        reset_flag = 0;
        Paint_DrawImage(Home, 0, 0, 240, 240); // Draw image at (50, 50) with dimensions 240*240
        Paint_DrawString_EN(50, 50, (String(main_val )).c_str(), &Font48, WHITE, WHITE);
        Paint_DrawString_EN(128, 185, (String(sensorValue)).c_str(), &Font20, WHITE, BLACK);
        Paint_DrawString_EN(55, 185, (String(mv_val)).c_str(), &Font20, WHITE, BLACK);
        Paint_DrawString_EN(111, 34, ("" + String(smoothedValue, .0f) + "%  ").c_str(), &Font16, WHITE, GREEN);
        if (log_mode != 0 ) {
          Paint_DrawString_EN(180, 108, ("Log ON"), &Font12, WHITE, WHITE);
          if (log_mode == 1) Paint_DrawString_EN(180, 120, ("Stable"), &Font12, WHITE, WHITE);
          if (log_mode == 2)Paint_DrawString_EN(180, 120, ("Interval"), &Font8, WHITE, WHITE);
          if (log_mode == 3)Paint_DrawString_EN(180, 120, ("Button"), &Font12, WHITE, WHITE);
        }
      }
      /////////////////////////////////////////////  STATUS == 2   ///////////////////////////////////////////////////////




      /////////////////////////////////////   STATUS == 3  /////////////////////////////////////////////////////////////
      else if (status == 3) {
        RESET();
        Paint_DrawImage(template1, 0, 0, 240, 240); // Draw image at (0,0) with dimensions 240*240
        Paint_DrawString_EN(50, 50, (String(CAL_VAL)).c_str(), &Font48, WHITE, WHITE);
        Paint_DrawString_EN(65, 110, ("BUFFER" /*+ String(battery_val)*/), &Font24, WHITE, WHITE);
        Paint_DrawString_EN(25, 140, ("CALIBRATING" /*+ String(battery_val)*/), &Font24, WHITE, WHITE);
        Paint_DrawString_EN(111, 34, ("" + String(smoothedValue, .0f) + "%  ").c_str(), &Font16, WHITE, GREEN);
      }
      /////////////////////////////////////   STATUS == 3  /////////////////////////////////////////////////////////////




      /////////////////////////////////////   STATUS == 4  /////////////////////////////////////////////////////////////
      //      else if (status == 4) {
      //        Paint_DrawString_EN(25, 90, ("BATTERY" /*+ String(battery_val)*/), &Font48, WHITE, RED);
      //        Paint_DrawString_EN(40, 150, ("LOW" /*String(BUFFER_VAL))*/), &Font48, WHITE, RED);
      //      }
      /////////////////////////////////////   STATUS == 4  /////////////////////////////////////////////////////////////



      /////////////////////////////////////   STATUS == 5  /////////////////////////////////////////////////////////////
      else if (status == 5) {
        RESET();
        Paint_DrawImage(template1, 0, 0, 240, 240); // Draw image at (50, 50) with dimensions 240*240
        Paint_DrawString_EN(30, 100, ("Press ok To Start" /*+ String(battery_val)*/), &Font16, WHITE, WHITE);
        Paint_DrawString_EN(45, 140, ("CALIBRATION" /*+ String(battery_val)*/), &Font20, WHITE, WHITE);
        Paint_DrawString_EN(111, 34, ("" + String(smoothedValue, .0f) + "%  ").c_str(), &Font16, WHITE, GREEN);

      }
      /////////////////////////////////////   STATUS == 5  /////////////////////////////////////////////////////////////





      /////////////////////////////////////   STATUS == 6  /////////////////////////////////////////////////////////////
      else if (status == 6) {
        RESET();
        Paint_DrawImage(timer, 0, 0, 240, 240); // Draw image at (50, 50) with dimensions 240*240}
        Paint_DrawString_EN(50, 50, ("" + String(CAL_TIME)).c_str(), &Font48, WHITE, WHITE);
        Paint_DrawString_EN(111, 34, ("" + String(smoothedValue, .0f) + "%  ").c_str(), &Font16, WHITE, GREEN);
      }
      /////////////////////////////////////   STATUS == 6  /////////////////////////////////////////////////////////////







      /////////////////////////////////////   STATUS == 7  ("  Buffer Value Printing  ")/////////////////////////////////////////////////////////////
      else if (status == 7) {
        RESET();
        Paint_DrawImage(mancal, 0, 0, 240, 240); // Draw image at (50, 50) with dimensions 240*240}
        Paint_DrawString_EN(144, 209, ("" + String(c)).c_str(), &Font16, WHITE, BLACK);
        Paint_DrawString_EN(50, 50, ("" + String(BUFFER_VAL)).c_str(), &Font48, WHITE, WHITE);
        Paint_DrawString_EN(111, 34, ("" + String(smoothedValue, .0f) + "%  ").c_str(), &Font16, WHITE, GREEN);
      }
      /////////////////////////////////////   STATUS == 7  /////////////////////////////////////////////////////////////





      /////////////////////////////////////   STATUS == 8  (" Buffer Change ")/////////////////////////////////////////////////////////////
      else if (status == 8) {
        RESET();
        Paint_DrawImage(mancalchange, 0, 0, 240, 240); // Draw image at (50, 50) with dimensions 240*240}
        Paint_DrawString_EN(145, 208, ("" + String(c)).c_str(), &Font16, WHITE, BLACK);
        Paint_DrawString_EN(50, 50, ("" + String(runner_val)).c_str(), &Font48, WHITE, WHITE);
        Paint_DrawString_EN(111, 34, ("" + String(smoothedValue, .0f) + "%  ").c_str(), &Font16, WHITE, GREEN);
      }
      /////////////////////////////////////   STATUS == 8    /////////////////////////////////////////////////////////////





      /////////////////////////////////////   STATUS == 9   ("LOG ON BUTTON ") /////////////////////////////////////////
      //      else if (status == 9) {
      //        RESET();
      //        Paint_DrawImage(logonbutton, 0, 0, 240, 240); // Draw image at (50, 50) with dimensions 240*240
      //        Paint_DrawString_EN(111, 34, ("" + String(smoothedValue, .0f) + "%  ").c_str(), &Font16, WHITE, GREEN);
      //      }
      /////////////////////////////////////   STATUS == 9  /////////////////////////////////////////////////////////////





      /////////////////////////////////////   STATUS == 10  /////////////////////////////////////////////////////////////
      else if (status == 10) {
        RESET();
        Paint_DrawString_EN(30, 100, ("MEMORY  FULL  "), &Font24, WHITE, RED);
        Paint_DrawString_EN(20, 150, ("Do you want to continue? "), &Font24, WHITE, RED);
      }
      /////////////////////////////////////   STATUS == 10  /////////////////////////////////////////////////////////////
      /////////////////////////////////////   STATUS == 11  /////////////////////////////////////////////////////////////
      else if (status == 11) {
        RESET();
        Paint_DrawImage(otapage, 0, 0, 240, 240); // Draw image at (50, 50) with dimensions 240*240
        Paint_DrawString_EN(20, 115, ("IP:-" + String(IP)).c_str(), &Font16, WHITE, WHITE);
        Paint_DrawString_EN(72, 49, ("PORT:-81" /*+ String(battery_val)*/), &Font16, WHITE, WHITE);
        Paint_DrawString_EN(60, 70, ("SSID:-aican" /*+ String(battery_val)*/), &Font16, WHITE, WHITE);
        Paint_DrawString_EN(40, 92, ("Pass:-raspberry" /*+ String(battery_val)*/), &Font16, WHITE, WHITE);
        //        digitalWrite(ESP_POWER, HIGH);
        ota_flag = 1;
      }

      /////////////////////////////////////   STATUS == 11  /////////////////////////////////////////////////////////////




      /////////////////////////////////////   STATUS == 12   Probe Health /////////////////////////////////////////////////////////////
      else if (status == 12) {
        RESET();
        reset_flag = 1;
        Paint_DrawImage(probe, 0, 0, 240, 240); // Draw image at (50, 50) with dimensions 240*240
        Paint_DrawString_EN(75, 55, ("" + String(slope1) + "%").c_str(), &Font20, WHITE, RED);// Slope 1
        Paint_DrawString_EN(143, 55, ("" + String(slope2) + "%").c_str(), &Font20, WHITE, RED);//Slope 2
        Paint_DrawString_EN(75, 95, ("" + String(slope3) + "%").c_str(), &Font20, WHITE, RED);// Slope 3
        Paint_DrawString_EN(143, 95, ("" + String(slope4) + "%").c_str(), &Font20, WHITE, RED);//Slope4
        Paint_DrawString_EN(70, 183, ("" + String(slope_main) + "%").c_str(), &Font20, WHITE, RED);//Slope Main
        Paint_DrawString_EN(150, 183, ("" + String(offset) + "%").c_str(), &Font20, WHITE, RED);//Offset
        Paint_DrawString_EN(111, 34, ("" + String(smoothedValue, .0f) + "%  ").c_str(), &Font16, WHITE, GREEN);// Battery Percentage
      }
      /////////////////////////////////////   STATUS == 12  /////////////////////////////////////////////////////////////
      LCD_1IN28_Display(BlackImage);
    }
  }
  //  }
}




















//###########################################################################################
//##########################        SLEEP      ##############################################
//###########################################################################################
void sleep_S() {
  sleep_flag = 1;
  Paint_Clear(BLUE);
  LCD_1IN28_Display(BlackImage);
  //  digitalWrite(ESP_POWER, LOW);
  //  delay(50);
  //  digitalWrite(ESP_POWER, HIGH);
  //  delay(1000);
  //  digitalWrite(ESP_POWER, LOW);
}
//###########################################################################################
//##########################        SLEEP      ##############################################
//###########################################################################################





//###########################################################################################
//##########################    POWER_ON/OFF   ##############################################
//###########################################################################################
void OF_ON() {
  if (power_flag == 0)digitalWrite(ESP_POWER, HIGH); power_flag = 1;
  sstatus = digitalRead(3);
  Serial.println(sstatus);
  if (millis() - startTime >= 15000 && sstatus == 1) {
    String runningdisp;
    digitalWrite(ESP_POWER, LOW);
    delay(50);
    digitalWrite(ESP_POWER, HIGH);
    Serial.println("POWER OFF");
    delay(2500);
    digitalWrite(ESP_POWER, LOW);
    delay(50);
    digitalWrite(MOSFET_PIN, LOW);
    digitalWrite(ON_PIN, LOW);
    startTime = millis();
  }
}
//###########################################################################################
//##########################    POWER_ON/OFF   ##############################################
//###########################################################################################





//*******************                                              ****************
//*******************  DELAY FOR MOVEMENT DETECTION AND PWER OFF   ****************
//*******************                                              ****************
void movement() {
  float movement = (gyro[0] + gyro[1] + gyro[2]);
  movement = (movement / 3) - 5;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 5000) {
    Serial.println(movement);
    previousMillis = currentMillis;
  }
  if (movement < -5 || movement > 5 || sstatus == 1 || reset_flag == 1) {
    previousMillis_OF = millis();
    previousMillis_sleep = millis();
    sleep_flag = 0 ;
    RESET();
    digitalWrite(ESP_POWER, HIGH);
    if (sstatus == 1) {
      Serial.println("power Switch Pressed");
    } else if (reset_flag == 1) {
      Serial.println("can't go to sleep device is in*** log||man_cal||other critical mood");
    } else {
      //      Serial.println("movement triggered");
    }
  }






  currentMillis_sleep = millis(); // Get the current time
  //  Serial.print("previousMillis_sleep");
  //  Serial.println(previousMillis_sleep);
  //  Serial.println(currentMillis_sleep - previousMillis_sleep);
  if (currentMillis_sleep - previousMillis_sleep >= 420000) {
    sleep_S();
    Serial.println("Sleep Triggered triggered");
    previousMillis_sleep = currentMillis_sleep;
  }




  if (sleep_flag == 1) {
    unsigned long currentMillis_OF = millis(); // Get the current time
    //    Serial.print("previousMillis_OF");
    //    Serial.println(previousMillis_OF);
    if (currentMillis_OF - previousMillis_OF >= 420000) {
      Serial.println("OFF_CONDITION");
      //      digitalWrite(ESP_POWER, LOW);
      //      delay(50);
      //      digitalWrite(ESP_POWER, HIGH);
      //      Serial.println("Powering off");
      //      delay(2500);
      //      digitalWrite(ESP_POWER, LOW);
      //      delay(50);
      //      digitalWrite(MOSFET_PIN, LOW);
      Paint_Clear(BLACK);
      LCD_1IN28_Display(BlackImage);
      digitalWrite(ON_PIN, LOW);
      previousMillis_OF = currentMillis_OF;
    }
  }
}
//*******************                                              ****************
//*******************  DELAY FOR MOVEMENT DETECTION AND PWER OFF   ****************
//*******************                                              ****************























//**************************************  use of second core ********************************


void setup1() {
  QMI8658_init();
  Serial1.begin(9600);
  Serial.begin(115200);
  pinMode(ESP_POWER, OUTPUT);
  pinMode(powerswitch, INPUT);
  pinMode(ON_PIN, OUTPUT);
  pinMode(MOSFET_PIN, OUTPUT);
  delay(2000);
  digitalWrite(ON_PIN, HIGH);
  digitalWrite(MOSFET_PIN, HIGH);
  digitalWrite(ESP_POWER, LOW);

  //  *********************************  averaging ***********************
  for (int i = 0; i < BUFFER_SIZE; i++) {
    readings[i] = 0;
  }
  //  **********************************  averaging **********************
}

void loop1() {
  if (ota_flag == 1)digitalWrite(ESP_POWER, HIGH); ota_flag = 0;
  //  QMI8658_read_xyz(acc, gyro, &tim_count);
  //  Serial.println("G11" + String(gyro[0])); Serial.println("G12" + String(gyro[1]));  Serial.println("G13" + String(gyro[2]));
  //  Serial.printf("C1: Stay on target...\n");
  OF_ON();
  averaging();
  //  movement();
  float bat_percentage = calculateBatteryPercentage(bat_val, minBatteryVoltage, maxBatteryVoltage);
  smoothedValue = movingAverage.update(bat_percentage);
  result = DEC_ADC_Read();
  bat_val = result * conversion_factor;
  if (bat_val < 3.36) {
    bat_val = bat_val - 0.15;
  }






  //*******************                                     ****************
  //*******************  TEMPRATURE READING AND AVERAGING   ****************
  //*******************                                     ****************
  float newReading = analogReadTemp();
  total = readings[index1];
  // Add the new reading
  readings[index1] = newReading;
  total += newReading;
  // Move to the next position in the circular buffer
  index1 = (index1 + 1) % BUFFER_SIZE;
  // Calculate the moving average
  average = (float)total / BUFFER_SIZE;
  //  Serial.println("RP2040 Onboard Temp " + String(average) + "*c");
  if (average > LIMIT) {
    digitalWrite(ESP_POWER, LOW);
  } else if (average < LIMIT) {
    digitalWrite(ESP_POWER, HIGH);
  }
  //*******************                                     ****************
  //*******************  TEMPRATURE READING AND AVERAGING   ****************
  //*******************                                     ****************
}



void RESET() {
  previousMillis_OF = millis();
  previousMillis_sleep = millis();
}
