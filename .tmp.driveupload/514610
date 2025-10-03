#include <U8g2lib.h>
#include <Wire.h>
#include <SoftwareWire.h>

// Software I2C on D2 (SDA), D3 (SCL)
SoftwareWire myWire(2, 3);  // SDA, SCL

// Initialize the OLED display using U8g2 and Software I2C
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/3, /* data=*/2, /* reset=*/U8X8_PIN_NONE);




const int potPin = A0;
const int pwmPin = 3;
const int sdPin = 2;
const int relay1 = 4;
const int relay2 = 5;
const int relay3 = 6;
const int relay4 = 7;
const int relay5 = 8;
bool isovrvolt = 0;
bool isudervoltage = 0;
bool relay1flag = 0;
bool relay2flag = 0;
bool relay3flag = 0;
bool relay4flag = 0;
bool relay5flag = 0;
float acVolt = 0;
const int OVR_LOAD = 11;     //OVER LOAD LED
const int OVR_VOLT = 13;     // over_voltage
const int UNDR_VOLT = A5;    // Under Voltage LED
const int foot_switch = 10;  // Foot switch pin // Low Bus PIN
int c = 0;
bool cflag = 0;
const int analogPin = A3;          // Pin connected to the output of the ACS712
const float sensitivity = 0.066;   // Sensitivity in V/A (adjust based on your ACS712 model)
const int zeroCurrentValue = 438;  // Analog value when current is 0 (midpoint of 1023)
const int numReadings = 100;       // Number of readings for the moving average


////////////////////////////////////     Calibbration /////////////////////////////
////////////////////////////////////     ADITYA       /////////////////////////////
////////////////////////////////////     CTR+SHIFT+U  /////////////////////////////

int V_90 = 37.9;
// int undervolt = 45.4;  //100  voltage
int V_110 = 52.4;
int V_135 = 70.1;
int V_170 = 95.3;
int V_200 = 117.1;
int V_230 = 137.9;
// int overvolt = 153.9;  // 250 voltage

////////////////////////////////////     Calibbration /////////////////////////////
////////////////////////////////////     ADITYA       /////////////////////////////
////////////////////////////////////     CTR+SHIFT+U  /////////////////////////////



//  int relay_select_ = 1;
//  int ovrload = 170;
int undervolt = -1;
int overvolt = 1025;
int ovrload = 1025;
int relay_select_ = 0;





// int V_90 = 34;
// int V_110 = 47.5;
// int V_135 = 64.4;
// int V_170 = 87.7;
// int V_200 = 107.8;
// int V_230 = 126.5;
// int ovrload = 173;
// // int undervolt = 40;
// int undervolt = -1;
// // int overvolt = 400;
// int overvolt = 141;







const int V_DC_ADC = A2;
int readingsA0[numReadings];  // Array to store readings for A0
int readingsA1[numReadings];  // Array to store readings for A1
int readingsA2[numReadings];  // Array to store readings for A2
int readingsA3[numReadings];  // Array to store readings for A3
int readIndex = 0;            // Current index in the array
float totalA0 = 0;            // Total of the readings for A0
float totalA1 = 0;            // Total of the readings for A1
float totalA2 = 0;            // Total of the readings for A2
float totalA3 = 0;            // Total of the readings for A3
float averageA0 = 0;          // Moving average for A0
float averageA1 = 0;          // Moving average for A1
float averageA2 = 0;          // Moving average for A2
float averageA3 = 0;          // Moving average for A3
const float adcPerAmp = 9.0;  // ADC change per amp (450 - 441 = 9)





int potValue = 0;                  // Variable to store the analog value from the potentiometer
int targetPwmValue = 0;            // Target PWM value based on potentiometer input
int currentPwmValue = 0;           // Current PWM value for smooth ramping
int rampStep = 3;                  // Step size for the ramp function
int rampDelay = 15;                // Delay time in milliseconds between ramp steps
int relayState = 0;                // To track the number of relays currently ON
unsigned long previousMillis = 0;  // Variable to store the last time delay started



float calculateCurrent(int rawADC) {
  float voltage = (rawADC / 1024.0) * 5.0;
  float current = (rawADC - zeroCurrentValue) / adcPerAmp;
  current = (current > 0) ? current : 0;
  return current;
}




void updateMovingAverage(int analogPin, int readings[], float &total, float &average) {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(analogPin);
  total = total + readings[readIndex];
  average = total / numReadings;
  readIndex = (readIndex + 1) % numReadings;  // Wrap around the array index
}





void overload() {
  unsigned long currentMillis = millis();  // Get the current time
  if (currentMillis - previousMillis >= 2000) {
    previousMillis = currentMillis;
    if (averageA3 > ovrload)  // Aps Set To Aprox 16 Amps
    {
      digitalWrite(OVR_LOAD, LOW);  // Turn On Over Load Led
      digitalWrite(sdPin, LOW);     // Disable motor
      while (1) {
        Serial.println("Over LOAD Detected");
        digitalWrite(OVR_LOAD, HIGH);
      }
    }
  }
}








void relayselect() {
  if (averageA1 <= V_90) {
    digitalWrite(relay1, HIGH);  // Relay 1 PIN
    digitalWrite(relay2, HIGH);  // Relay 2 PIN
    digitalWrite(relay3, HIGH);  // Relay 3 PIN
    digitalWrite(relay4, HIGH);  // Relay 4 PIN
    digitalWrite(relay5, HIGH);  // Relay 5 PIN
    Serial.println("4 Relay ");
    Serial.println("90_VOLT_BINDING  ");
  } else if (averageA1 <= V_110 && averageA1 > V_90) {
    digitalWrite(relay1, HIGH);  // Relay 1 PIN
    digitalWrite(relay2, HIGH);  // Relay 2 PIN
    digitalWrite(relay3, HIGH);  // Relay 3 PIN
    digitalWrite(relay4, HIGH);  // Relay 4 PIN
    digitalWrite(relay5, LOW);   // Relay 5 PIN
    Serial.println("4 Relay ");
    Serial.println("110_VOLT_BINDING  ");
  } else if (averageA1 <= V_135 && averageA1 > V_110) {
    digitalWrite(relay1, HIGH);  // Relay 1 PIN
    digitalWrite(relay2, HIGH);  // Relay 2 PIN
    digitalWrite(relay3, HIGH);  // Relay 3 PIN
    digitalWrite(relay4, LOW);   // Relay 4 PIN
    digitalWrite(relay5, LOW);   // Relay 5 PIN
    Serial.println("3 Relay ");
    Serial.println("135_VOLT_BINDING  ");
  } else if (averageA1 <= V_170 && averageA1 > V_135) {
    digitalWrite(relay1, HIGH);  // Relay 1 PIN
    digitalWrite(relay2, HIGH);  // Relay 2 PIN
    digitalWrite(relay3, LOW);   // Relay 3 PIN
    digitalWrite(relay4, LOW);   // Relay 4 PIN
    digitalWrite(relay5, LOW);   // Relay 5 PIN
    Serial.println("2 Relay ");
    Serial.println("170_VOLT_BINDING  ");
  } else if (averageA1 <= V_200 && averageA1 > V_170) {
    digitalWrite(relay1, HIGH);  // Relay 1 PIN
    digitalWrite(relay2, LOW);   // Relay 2 PIN
    digitalWrite(relay3, LOW);   // Relay 3 PIN
    digitalWrite(relay4, LOW);   // Relay 4 PIN
    digitalWrite(relay5, LOW);   // Relay 5 PIN
    Serial.println("1 Relay ");
    Serial.println("200_VOLT_BINDING  ");
  } else if (averageA1 <= V_230 && averageA1 > V_200) {
    digitalWrite(relay1, LOW);  // Relay 1 PIN
    digitalWrite(relay2, LOW);  // Relay 2 PIN
    digitalWrite(relay3, LOW);  // Relay 3 PIN
    digitalWrite(relay4, LOW);  // Relay 4 PIN
    digitalWrite(relay5, LOW);  // Relay 5 PIN
    Serial.println("NO Relay ON");
    Serial.println("230_VOLT_BINDING  ");
  }
}







void setup() {

  //#############################     PIN DEFINITION    START       #####################################
  //*******************    DRIVER IC PIN DECIFINITION **********************
  pinMode(pwmPin, OUTPUT);    // PWM PIN
  pinMode(sdPin, OUTPUT);     // EN/Disable Pin Main Motor
  digitalWrite(sdPin, HIGH);  // En Pin High To Drive Motor
  //************************          END          *************************
  pinMode(foot_switch, INPUT_PULLUP);
  //*************     LED PIN DEFINITION STARTED     ***********************
  pinMode(OVR_VOLT, OUTPUT);   // LED 1 Difinition
  pinMode(UNDR_VOLT, OUTPUT);  // LED 2 Difinition
  pinMode(OVR_LOAD, OUTPUT);   // LED 3 Difinition
  //********************        END       **********************************

  //***********************   Relay Pin Definition Started *****************
  pinMode(relay1, OUTPUT);  // Relay 1 PIN
  pinMode(relay2, OUTPUT);  // Relay 2 PIN
  pinMode(relay3, OUTPUT);  // Relay 3 PIN
  pinMode(relay4, OUTPUT);  // Relay 4 PIN
  pinMode(relay5, OUTPUT);  // Relay 5 PIN
  //************************        END       ******************************



  //*************************    RELAY PIN  SET   **************************
  //  digitalWrite(relay1, HIGH);  // Relay 1 PIN
  //  digitalWrite(relay2, HIGH);  // Relay 2 PIN
  //  digitalWrite(relay3, HIGH);  // Relay 3 PIN
  //  digitalWrite(relay4, HIGH);  // Relay 4 PIN
  //  digitalWrite(relay5, HIGH);  // Relay 5 PIN
  //**************************          END       *************************

  Serial.begin(115200);  // Boud Rate Definition

  u8g2.setBus(&myWire);
  u8g2.begin();
  u8g2.enableUTF8Print();  // Enable UTF-8 support


  /////////////////////   On Start Delay ////////////////////////////
  for (int start_counter = 0; start_counter < 10; start_counter++) {
    digitalWrite(OVR_VOLT, LOW);   // LED 1 ON
    digitalWrite(UNDR_VOLT, LOW);  // LED 2 ON
    digitalWrite(OVR_LOAD, LOW);   // LED 3 ON
    delay(500);
    digitalWrite(OVR_VOLT, HIGH);   // LED 1 OFF
    digitalWrite(UNDR_VOLT, HIGH);  // LED 2 OFF
    digitalWrite(OVR_LOAD, HIGH);   // LED 3 OFF
    delay(500);
  }
  /////////////////////   On Start Delay ////////////////////////////

  //######################   LED PIN ################################
  digitalWrite(OVR_VOLT, LOW);   // LED 1 OUTPUT LOW
  digitalWrite(UNDR_VOLT, LOW);  // LED 1 OUTPUT LOW
  digitalWrite(OVR_LOAD, LOW);   // LED 2 OUTPUT LOW
  //######################   LED PIN ###############################



  //********************      ADC Averaging Loop    *************************
  for (int i = 0; i < numReadings; i++) {
    readingsA0[i] = 0;
    readingsA1[i] = 0;
    readingsA2[i] = 0;
    readingsA3[i] = 0;
  }
  //**************************          END       *************************










  //**********      TAKING AVERAGE OF 100 Reading  PRIOR  *****************
  while (c < 100) {
    updateMovingAverage(A0, readingsA0, totalA0, averageA0);  // POTENTIOMETER PIN READING
    updateMovingAverage(A1, readingsA1, totalA1, averageA1);  // AC VOLTAGE REDING PIN
    updateMovingAverage(A2, readingsA2, totalA2, averageA2);  // DC CURRENT READING PIN
    updateMovingAverage(A3, readingsA3, totalA3, averageA3);  // Dv Voltage Reading Pin
    c = c + 1;
    Serial.println(c);
  }
  //**************************          END       *************************




  //  ############################   Setting FIX Frequency On OUTPUT   ###################################


  //////////////////////////////   For 1 KHZ ///////////////////////////

  cli();  // Disable global interrupts

  TCCR2A = (1 << WGM21) | (1 << WGM20);  // Fast PWM mode with OCR2A as TOP
  TCCR2B = (1 << WGM22) | (1 << CS22);   // Prescaler = 64

  OCR2A = 249;  // TOP value for 1 kHz
  OCR2B = 0;    // Initial 0% duty cycle

  TCCR2A |= (1 << COM2B1);  // Non-inverting mode on OC2B (clear on compare match)

  sei();  // Enable global interrupts

  //////////////////////////////   For 1 KHZ ///////////////////////////







  //////////////////////////////   For 2 KHZ ///////////////////////////

  // cli();
  // TCCR2A = (1 << WGM21) | (1 << WGM20);  // Set Fast PWM mode
  // TCCR2B = (1 << CS21);                  // No prescaler (CS20 = 1), prescaler = 1
  // OCR2B = 0;                             // Initial 0% duty cycle
  // TCCR2A |= (1 << COM2B1);               // Clear OC2B on Compare Match, set OC2B at BOTTOM
  // sei();
  //////////////////////////////   For 2 KHZ ///////////////////////////

  //########################################          END       ###########################################
}








void loop() {
  int t = digitalRead(foot_switch);
  // Serial.println("Foot_Switch");
  Serial.println(t);
  // Serial.print("                                  ");
  // Serial.println(relay_select_);

  updateMovingAverage(A0, readingsA0, totalA0, averageA0);
  updateMovingAverage(A1, readingsA1, totalA1, averageA1);
  updateMovingAverage(A2, readingsA2, totalA2, averageA2);
  updateMovingAverage(A3, readingsA3, totalA3, averageA3);
  float current = calculateCurrent(averageA3);
  acVolt = (averageA1 + 2.424) / 0.774;
  if (averageA1 > overvolt) {
    isovrvolt = 1;
    digitalWrite(sdPin, LOW);      // Disable motor
    digitalWrite(OVR_VOLT, HIGH);  // Turn on overvoltage LED
    while (1) {
      Serial.println("Over Voltage Detected");
    }
  } else if (averageA1 < undervolt) {
    isudervoltage = 1;
    pinMode(UNDR_VOLT, OUTPUT);
    digitalWrite(sdPin, LOW);       // Disable motor
    digitalWrite(UNDR_VOLT, HIGH);  // Turn on undervoltage LED
    Serial.println("Undervoltage detected");
  }








  if (isudervoltage == 0 && t == 1)  // isovrvolt == 0 && isudervoltage == 0)
  {
    overload();
    potValue = analogRead(potPin);
    targetPwmValue = map(potValue, 0, 1000, 0, 200);
    rampPWM(currentPwmValue, targetPwmValue);
    digitalWrite(sdPin, rampPWM < 10 ? LOW : HIGH);




    //     Debugging Section
    // Serial.print("Potentiometer Value: ");
    // Serial.print(potValue);
    // Serial.print(" -> Target PWM Value: ");
    // Serial.print(targetPwmValue);
    // Serial.print(" -> Current PWM Value: ");
    // Serial.println(currentPwmValue);
    // Serial.print("Current (Averaged): ");
    // Serial.print(current);
    // Serial.println(" A");
    // Serial.print("Average A0: ");
    // Serial.println(averageA0);
    // Serial.print("AC_VOLTAGE A1:            ");
    // Serial.println(averageA1);
    // Serial.print("Average A2: ");
    // Serial.println(averageA2);
    // Serial.print("MOTOR A3: ");
    // Serial.println(averageA3);
    // Serial.print(averageA1);
    // Serial.print(",");
    // Serial.println(averageA3);
    // Print to OLED
    u8g2.clearBuffer();  // Clear display buffer
    u8g2.setFont(u8g2_font_ncenB08_tr);  // Set font

    u8g2.setCursor(0, 15);
    u8g2.print("AC=");
    u8g2.print(acVolt, 1);  // Show AC voltage to 1 decimal

    u8g2.setCursor(0, 35);
    u8g2.print("M=");
    u8g2.print(averageA3, 1);  // Show motor value to 1 decimal

    u8g2.sendBuffer();  // Display buffer content

    delay(10);
    if (relay_select_ == 1) {
      relayselect();
    }
  } else {
    digitalWrite(sdPin, LOW);
  }
  // } else {
  //   Serial.println("Foot_Switch_pressed");
  //   // digitalWrite(sdPin, LOW);
  // }
}





void rampPWM(int &current, int target) {
  if (current < target) {
    current += rampStep;     // Increase PWM towards target
    if (current > target) {  // Ensure it does not exceed target
      current = target;
    }
  } else if (current > target) {
    current -= rampStep;     // Decrease PWM towards target
    if (current < target) {  // Ensure it does not fall below target
      current = target;
    }
  }
  OCR2B = current;
  delay(rampDelay);
}
