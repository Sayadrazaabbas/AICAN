#ifndef SOCKET_H
#define SOCKET_H

#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include <Ticker.h>
#include <WiFi.h>

// Declare global server and websocket objects
extern AsyncWebServer server;
extern WebSocketsServer websockets;

// Extern variables that must be defined elsewhere in your project
extern int calButton;
extern int start_ph_cal;
extern float manual_atc;
extern int cal_mode;
extern int atc_var;
extern int Ro;
extern int manual_calibration_flag;
extern float log_mode;
extern float bufferValue[5];
extern float R_C;
extern int SENSORSELECT;

// Function declarations
void notFound(AsyncWebServerRequest *request);
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
JsonVariant findNestedKey(JsonObject obj, const char* key);
void wifi_socket();
void data_sender(String x, String y);

#endif
