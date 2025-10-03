#include <ESPmDNS.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80); // server port 80
WebSocketsServer websockets(81);
#include <Ticker.h>

//int count = 0;
char webpage[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>

<script>

var connection = new WebSocket('ws://'+location.hostname+':81/');

var temp_data = 0;
var hum_data = 0;
connection.onmessage = function(event){

  var full_data = event.data;
  console.log(full_data);
  var data = JSON.parse(full_data);
}
</script>
</html>
)=====";
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}

JsonVariant findNestedKey(JsonObject obj, const char* key) {
    JsonVariant foundObject = obj[key];
    if (!foundObject.isNull())
        return foundObject;

    for (JsonPair pair : obj) {
        JsonVariant nestedObject = findNestedKey(pair.value(), key);
        if (!nestedObject.isNull())
            return nestedObject;
    }

    return JsonVariant();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type)
  {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      digitalWrite(24, LOW);
      break;
    case WStype_CONNECTED: {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        digitalWrite(24, HIGH);
      }
      break;
    case WStype_TEXT:
//      Serial.printf("[%u] get Text: %s\n", num, payload);
      String message = String((char*)( payload));
      Serial.println(message);


     DynamicJsonDocument doc(200);
    // deserialize the data
    DeserializationError error = deserializeJson(doc, message);
    // parse the parameters we expect to receive (TO-DO: error handling)
      // Test if parsing succeeds.
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  if(!findNestedKey(doc.as<JsonObject>(), "CAL").isNull()) {calButton = int(findNestedKey(doc.as<JsonObject>(), "CAL")); Serial.print("calButton = ");Serial.println(calButton);
  Serial.println("*********************************************************");
  Serial.println(calButton);
  Serial.println("*********************************************************");
  Serial.println("");
  if (calButton == 10 || calButton == 20 || calButton == 30 || calButton == 40 || calButton == 50) {
      start_ph_cal = 1;
    }
  }
if(!findNestedKey(doc.as<JsonObject>(), "ATC_AT").isNull()) {manual_atc = float(findNestedKey(doc.as<JsonObject>(), "ATC_AT")); Serial.println(manual_atc);}//ATC VALUE 
  if(!findNestedKey(doc.as<JsonObject>(), "CAL_MODE").isNull()) {cal_mode = int(findNestedKey(doc.as<JsonObject>(), "CAL_MODE")); Serial.println(cal_mode);EEPROM.put(410, cal_mode); EEPROM.commit();}   
  if(!findNestedKey(doc.as<JsonObject>(), "ATC").isNull()) { atc_var = int(findNestedKey(doc.as<JsonObject>(), "ATC")); Serial.println(atc_var);}//ATC 
  if(!findNestedKey(doc.as<JsonObject>(), "T_SET").isNull()) {Ro = int(findNestedKey(doc.as<JsonObject>(), "T_SET")); Serial.println(Ro);EEPROM.put(450, Ro);}//????????????????
  if(!findNestedKey(doc.as<JsonObject>(), "MANUAL").isNull()) {manual_calibration_flag = int(findNestedKey(doc.as<JsonObject>(), "MANUAL")); Serial.println(manual_calibration_flag);}
  if(!findNestedKey(doc.as<JsonObject>(), "AUTOLOG").isNull()) {log_mode = int(findNestedKey(doc.as<JsonObject>(), "AUTOLOG")); Serial.println(log_mode);}      
  if(!findNestedKey(doc.as<JsonObject>(), "B_1").isNull()) {bufferValue[0] = float(findNestedKey(doc.as<JsonObject>(), "B_1")); Serial.println(bufferValue[0]); write_buffer_EEPROM();}
  if(!findNestedKey(doc.as<JsonObject>(), "B_2").isNull()) {bufferValue[1] = float(findNestedKey(doc.as<JsonObject>(), "B_2")); Serial.println(bufferValue[1]); write_buffer_EEPROM();}
  if(!findNestedKey(doc.as<JsonObject>(), "B_3").isNull()) {bufferValue[2] = float(findNestedKey(doc.as<JsonObject>(), "B_3")); Serial.println(bufferValue[2]); write_buffer_EEPROM();}
  if(!findNestedKey(doc.as<JsonObject>(), "B_4").isNull()) {bufferValue[3] = float(findNestedKey(doc.as<JsonObject>(), "B_4")); Serial.println(bufferValue[3]); write_buffer_EEPROM();}
  if(!findNestedKey(doc.as<JsonObject>(), "B_5").isNull()) {bufferValue[4] = float(findNestedKey(doc.as<JsonObject>(), "B_5")); Serial.println(bufferValue[4]); write_buffer_EEPROM();}
  if(!findNestedKey(doc.as<JsonObject>(), "R_C").isNull()) {R_C = float(findNestedKey(doc.as<JsonObject>(), "R_C")); Serial.println(R_C);  EEPROM.put(500, R_C); EEPROM.commit();}
  if(!findNestedKey(doc.as<JsonObject>(), "THERM_VAL").isNull()) {SENSORSELECT = float(findNestedKey(doc.as<JsonObject>(), "THERM_VAL")); Serial.println("SENSORSELECT");Serial.println(SENSORSELECT);EEPROM.put(510, SENSORSELECT); EEPROM.commit();}

  }
}

void wifi_socket(){
  WiFi.softAP("EPT2006", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());


  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS responder started");
  }

  server.on("/", [](AsyncWebServerRequest * request)
  { request->send_P(200, "text/html", webpage);
  });


  server.onNotFound(notFound);

  server.begin();  // it will start webserver
  websockets.begin();
  websockets.onEvent(webSocketEvent);

}

void data_sender(String x, String y){
  String JSON_Data = "{\"DEVICE_ID\":";
               JSON_Data += "\"";
               JSON_Data += "EPT2006";
               JSON_Data += "\"";
               JSON_Data += ",\"";
               JSON_Data += x;
               JSON_Data += "\":";
               JSON_Data += "\"";
               JSON_Data += y;
               JSON_Data += "\"";
               JSON_Data += "}";
               Serial.println("***************************************");
        Serial.println(JSON_Data);
        websockets.broadcastTXT(JSON_Data);
        Serial.println("send loop");
        Serial.println("***************************************");
}
