float acc[3], gyro[3];
unsigned int tim_count = 0;
uint16_t result;
const unsigned long delayDuration = 5000;  // 1000 milliseconds = 1 second
int conectivity_flag = 1;
const float conversion_factor = 3.3f / (1 << 12) * 2;
// Variables to store the current time and the previous time
unsigned long currentTime = 0;
unsigned long previousTime = 0;
unsigned long previousMillis_OF = 0;   // Store the last time the action was performed
unsigned long previousMillis_sleep = 0;   // Store the last time the action was performed
unsigned long currentMillis_sleep = 0;
int sleep_flag = 0;
int ota_flag = 0;
float bat_val;
float batteryVoltage = 3.7; // Replace with the actual battery voltage
float minBatteryVoltage = 3.3;
float maxBatteryVoltage = 4.1;
int power_flag = 0;
int reset_flag = 0;
int status = 1;
float average = 0; // internal temprature stable reading
#define BUFFER_SIZE 50
float readings[BUFFER_SIZE];
int index1 = 0;
float total = 0;
StaticJsonDocument<1024> jsonDoc;
float sensorValue = 0;
float movingAvg = 0;
const int windowSize = 10; // Adjust the window size as needed
float reading[windowSize]; // Array to store sensor readings
int currentIndex = 0; // Index for circular buffer
