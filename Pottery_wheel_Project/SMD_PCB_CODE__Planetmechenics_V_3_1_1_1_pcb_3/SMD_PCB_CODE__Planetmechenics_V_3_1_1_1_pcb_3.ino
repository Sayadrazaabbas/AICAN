#define SENSOR_PIN A1
#define NUM_SAMPLES 1000
#define ADC_REF 5.0  // Vref for ADC
#define ADC_RES 1024.0
float calibrationFactor = 220.0 / 1.4;  // Adjust this after calibration



const int potPin = A0;
const int pwmPin = 3;
const int sdPin = 2;
const int relay1 = 4;
const int relay2 = 5;
const int relay3 = 6;
const int relay4 = 7;
const int relay5 = 8;
const int MOTOR_PIN = A4;
#define MAX_FEEDBACK 160
bool isstart = 0;
bool isovrvolt = 0;
bool isudervoltage = 0;
bool relay1flag = 0;
bool relay2flag = 0;
bool relay3flag = 0;
bool relay4flag = 0;
bool relay5flag = 0;
float acVolt = 0;
const int V_DC_ADC = A2;

const int OVR_LOAD = 13;     //OVER LOAD LED
const int OVR_VOLT = A5;     // over_voltage
const int UNDR_VOLT = 11;    // Under Voltage LED
const int foot_switch = 10;  // Foot switch pin // Low Bus PIN
int c = 0;
bool cflag = 0;
const int analogPin = A3;          // Pin connected to the output of the ACS712
const float sensitivity = 0.066;   // Sensitivity in V/A (adjust based on your ACS712 model)
const int zeroCurrentValue = 438;  // Analog value when current is 0 (midpoint of 1023)
const int numReadings = 150;       // Number of readings for the moving average




int V_90 = 90;
int V_110 = 110;
int V_135 = 134;
int V_170 = 150;
int V_200 = 162;
int V_230 = 172;
int ovrload = 370;
int undervolt = 100;
// int undervolt = -1;
int overvolt = 179.40;
// int overvolt = 178;


int readingsA2[numReadings];  // Array to store readings for A2
int readingsA3[numReadings];  // Array to store readings for A3
int readingsA4[numReadings];  // Array to store readings for A3
int readIndex = 0;            // Current index in the array
float totalA2 = 0;            // Total of the readings for A2
float totalA3 = 0;            // Total of the readings for A3
float totalA4 = 0;            // Total of the readings for A3
float averageA1 = 0;          // Moving average for A1
float averageA2 = 0;          // Moving average for A2
float averageA3 = 0;          // Moving average for A3
float averageA4 = 0;          // Moving average for A3
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
      digitalWrite(OVR_LOAD, LOW);
      digitalWrite(sdPin, LOW);  // Disable motor
      while (1) {
        Serial.println("Over LOAD Detected");
        digitalWrite(OVR_LOAD, HIGH);
      }
    }
  }
}




float getMovingAverage(float voltage) {
  const int numSamples = 50;
  static float samples[numSamples] = { 0 };
  static int index = 0;
  static float total = 0;

  total -= samples[index];
  samples[index] = voltage;
  total += samples[index];

  index = (index + 1) % numSamples;

  return total / numSamples;
}




// int getMovingAverageA4() {
//   const int numReadings = 200;
//   static int readings[numReadings];
//   static int index = 0;
//   static long total = 0;

//   int newReading = analogRead(A4);

//   total -= readings[index];      // Subtract the oldest reading
//   readings[index] = newReading;  // Store the new reading
//   total += newReading;           // Add the new reading
//   index = (index + 1) % numReadings;

//   return total / numReadings;  // Return average
// }





void relayselect() {
  // Serial.println("Relay select");
  // Serial.println(averageA1);
  if (averageA1 <= V_90) {
    digitalWrite(relay1, HIGH);  // Relay 1 PIN
    digitalWrite(relay2, HIGH);  // Relay 2 PIN
    digitalWrite(relay3, HIGH);  // Relay 3 PIN
    digitalWrite(relay4, HIGH);  // Relay 4 PIN
    digitalWrite(relay5, HIGH);  // Relay 5 PIN
    Serial.print("5 Relay");
    Serial.println("90_VOLT_BINDING  ");
  } else if (averageA1 <= V_110 && averageA1 > V_90) {
    digitalWrite(relay1, HIGH);  // Relay 1 PIN
    digitalWrite(relay2, HIGH);  // Relay 2 PIN
    digitalWrite(relay3, HIGH);  // Relay 3 PIN
    digitalWrite(relay4, HIGH);  // Relay 4 PIN
    digitalWrite(relay5, LOW);   // Relay 5 PIN
    Serial.print("4 Relay ");
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
  Serial.begin(115200);  // Boud Rate Definition
  //#############################     PIN DEFINITION    START       #####################################
  //*******************    DRIVER IC PIN DECIFINITION **********************
  pinMode(pwmPin, OUTPUT);    // PWM PIN
  pinMode(sdPin, OUTPUT);     // EN/Disable Pin Main Motor
  digitalWrite(sdPin, HIGH);  // En Pin High To Drive Motor
  //************************          END          *************************
  pinMode(10, INPUT_PULLUP);
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


  //######################   LED PIN ################################
  digitalWrite(OVR_VOLT, HIGH);   // LED 1 OUTPUT LOW
  digitalWrite(UNDR_VOLT, HIGH);  // LED 1 OUTPUT LOW
  digitalWrite(OVR_LOAD, HIGH);   // LED 2 OUTPUT LOW
  //######################   LED PIN ###############################



  /////////////////////   On Start Delay ////////////////////////////
  for (int start_counter = 0; start_counter < 10; start_counter++) {
    digitalWrite(OVR_VOLT, HIGH);   // LED 1 ON
    digitalWrite(UNDR_VOLT, HIGH);  // LED 2 ON
    digitalWrite(OVR_LOAD, HIGH);   // LED 3 ON
    delay(500);
    digitalWrite(OVR_VOLT, LOW);   // LED 1 OFF
    digitalWrite(UNDR_VOLT, LOW);  // LED 2 OFF
    digitalWrite(OVR_LOAD, LOW);   // LED 3 OFF
    delay(500);
  }
  /////////////////////   On Start Delay ////////////////////////////




  //********************      ADC Averaging Loop    *************************
  for (int i = 0; i < numReadings; i++) {
    readingsA2[i] = 0;
    readingsA3[i] = 0;
    readingsA4[i] = 0;
  }
  //**************************          END       *************************










  //**********      TAKING AVERAGE OF 100 Reading  PRIOR  *****************
  while (c < 100) {
    updateMovingAverage(A2, readingsA2, totalA2, averageA2);  // DC CURRENT READING PIN
    updateMovingAverage(A3, readingsA3, totalA3, averageA3);  // Dv Voltage Reading Pin
    updateMovingAverage(A4, readingsA4, totalA4, averageA4);  // Dv Voltage Reading Pin
    c = c + 1;
    Serial.println(c);
  }
  //**************************          END       *************************

  // for (int i = 0; i < 50; i++) {
  //   float voltage = analogRead(A1);  // Replace with your actual voltage read logic
  //   averageA1 = getMovingAverage(voltage);
  //   // delay(10);  // Small delay to mimic real-time sampling (optional)
  // }


  //  ############################   Setting FIX Frequency On OUTPUT   ###################################
  cli();
  TCCR2A = (1 << WGM21) | (1 << WGM20);  // Set Fast PWM mode
  TCCR2B = (1 << CS21);                  // No prescaler (CS20 = 1), prescaler = 1
  OCR2B = 0;                             // Initial 0% duty cycle
  TCCR2A |= (1 << COM2B1);               // Clear OC2B on Compare Match, set OC2B at BOTTOM
  sei();
  //########################################          END       ###########################################
}








void loop() {
  updateMovingAverage(A2, readingsA2, totalA2, averageA2);
  updateMovingAverage(A3, readingsA3, totalA3, averageA3);



  int minVal = 1023;
  int maxVal = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    int val = analogRead(SENSOR_PIN);
    if (val < minVal) minVal = val;
    if (val > maxVal) maxVal = val;
  }

  // Convert to voltages
  float voltageMin = (minVal * ADC_REF) / ADC_RES;
  float voltageMax = (maxVal * ADC_REF) / ADC_RES;
  float Vpp = voltageMax - voltageMin;  // Peak-to-peak voltage
  float Vrms = (Vpp / 2.0) * 0.7071;    // Assuming sine wave
  float voltage = Vrms * calibrationFactor;
  if (isstart == 0) {
    isstart = 1;
    for (int i = 0; i < 100; i++) {
      averageA1 = getMovingAverage(voltage);
    }
  }
  averageA1 = getMovingAverage(voltage);




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








  if (isudervoltage == 0)  // isovrvolt == 0 && isudervoltage == 0)
  {
    potValue = analogRead(potPin);
    targetPwmValue = map(potValue, 0, 1000, 0, 248);
    rampPWM(currentPwmValue, targetPwmValue);
    digitalWrite(sdPin, rampPWM < 10 ? LOW : HIGH);


    //      Debugging Section
    // Serial.print("Current (Averaged): ");
    Serial.print("AC VOLTAGE A1:    ");
    Serial.println(averageA1);
    // Serial.print("Average A2: ");
    // Serial.println(averageA2);
    Serial.print("Motor current  A3: ");
    Serial.println(averageA3);
    // Serial.print(" MOTOR_ADC =");
    // Serial.println(averageA4);

    delay(10);
    relayselect();
    overload();
  } else {
    digitalWrite(sdPin, LOW);
  }
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
