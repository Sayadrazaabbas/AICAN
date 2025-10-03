#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>   //////////////////////////// 01/10/2025
#include <HTTPClient.h>
#include <AsyncTCP.h>

// #include <WebServer.h>      //////////////////////////// 01/10/2025
// #include <Update.h>
//#include "wifi_manager.h"
#include "globalVar.h"
#include "display.h"
#include "EEPROM1.h"
#include "socket.h"
#include "adc.h"
#include "phSensor.h"
#include "OTA.h"
#include "values.h"
#include "manual.h"
#include "calibration.h"
