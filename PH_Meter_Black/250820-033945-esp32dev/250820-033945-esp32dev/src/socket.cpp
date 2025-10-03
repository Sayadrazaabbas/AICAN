#include "socket.h"
#include <EEPROM.h>

// Define global server and websockets here
AsyncWebServer server(80);
WebSocketsServer websockets(81);

// Webpage stored in PROGMEM
const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<script>
var connection = new WebSocket('ws://'+location.hostname+':81/');
connection.onmessage = function(event){
  var full_data = event.data;
  console.log(full_data);
  var data = JSON.parse(full_data);
}
</script>
</html>
)rawliteral";

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Page Not found");
}

JsonVariant findNestedKey(JsonObject obj, const char* key) {
    JsonVariant foundObject = obj[key];
    if (!foundObject.isNull()) return foundObject;

    for (JsonPair pair : obj) {
        JsonVariant nestedObject = findNestedKey(pair.value(), key);
        if (!nestedObject.isNull()) return nestedObject;
    }
    return JsonVariant();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            digitalWrite(24, LOW);
            break;

        case WStype_CONNECTED: {
            IPAddress ip = websockets.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n",
                          num, ip[0], ip[1], ip[2], ip[3], payload);
            digitalWrite(24, HIGH);
        }
        break;

        case WStype_TEXT: {
            String message = String((char*)payload);
            Serial.println(message);

            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, message);

            if (error) {
                Serial.print("deserializeJson() failed: ");
                Serial.println(error.c_str());
                return;
            }

            JsonObject obj = doc.as<JsonObject>();

            if (!findNestedKey(obj, "CAL").isNull()) {
                calButton = int(findNestedKey(obj, "CAL"));
                Serial.printf("calButton = %d\n", calButton);
                if (calButton == 10 || calButton == 20 || calButton == 30 ||
                    calButton == 40 || calButton == 50) {
                    start_ph_cal = 1;
                }
            }

            if (!findNestedKey(obj, "ATC_AT").isNull())
                manual_atc = float(findNestedKey(obj, "ATC_AT"));

            if (!findNestedKey(obj, "CAL_MODE").isNull()) {
                cal_mode = int(findNestedKey(obj, "CAL_MODE"));
                EEPROM.put(410, cal_mode);
                EEPROM.commit();
            }

            if (!findNestedKey(obj, "ATC").isNull())
                atc_var = int(findNestedKey(obj, "ATC"));

            if (!findNestedKey(obj, "T_SET").isNull()) {
                Ro = int(findNestedKey(obj, "T_SET"));
                EEPROM.put(450, Ro);
            }

            if (!findNestedKey(obj, "MANUAL").isNull())
                manual_calibration_flag = int(findNestedKey(obj, "MANUAL"));

            if (!findNestedKey(obj, "AUTOLOG").isNull())
                log_mode = int(findNestedKey(obj, "AUTOLOG"));

            if (!findNestedKey(obj, "B_1").isNull()) { bufferValue[0] = float(findNestedKey(obj, "B_1")); }
            if (!findNestedKey(obj, "B_2").isNull()) { bufferValue[1] = float(findNestedKey(obj, "B_2")); }
            if (!findNestedKey(obj, "B_3").isNull()) { bufferValue[2] = float(findNestedKey(obj, "B_3")); }
            if (!findNestedKey(obj, "B_4").isNull()) { bufferValue[3] = float(findNestedKey(obj, "B_4")); }
            if (!findNestedKey(obj, "B_5").isNull()) { bufferValue[4] = float(findNestedKey(obj, "B_5")); }

            if (!findNestedKey(obj, "R_C").isNull()) {
                R_C = float(findNestedKey(obj, "R_C"));
                EEPROM.put(500, R_C);
                EEPROM.commit();
            }

            if (!findNestedKey(obj, "THERM_VAL").isNull()) {
                SENSORSELECT = float(findNestedKey(obj, "THERM_VAL"));
                EEPROM.put(510, SENSORSELECT);
                EEPROM.commit();
            }
        }
        break;
    }
}

void wifi_socket() {
    WiFi.softAP("EPT2006", "");
    Serial.println("SoftAP started");
    Serial.println(WiFi.softAPIP());

    if (MDNS.begin("ESP")) {
        Serial.println("MDNS responder started");
    }

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", webpage);
    });

    server.onNotFound(notFound);

    server.begin();
    websockets.begin();
    websockets.onEvent(webSocketEvent);
}

void data_sender(String x, String y) {
    String JSON_Data = "{\"DEVICE_ID\":\"EPT2006\",\"" + x + "\":\"" + y + "\"}";
    Serial.println("***************************************");
    Serial.println(JSON_Data);
    websockets.broadcastTXT(JSON_Data);
    Serial.println("send loop");
    Serial.println("***************************************");
}
