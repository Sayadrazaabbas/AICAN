#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>

// ==== SoftAP Credentials ====
const char* apSSID = "espota";
const char* apPassword = "12345678";

// ==== Web server on port 80 ====
WebServer server(80);

// ==== HTML Page for OTA Upload ====
const char* uploadPage PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP32 OTA Update</title>
  </head>
  <body>
    <h2>ESP32 OTA Update (Access Point Mode)</h2>
    <form method="POST" action="/update" enctype="multipart/form-data">
      <input type="file" name="update">
      <input type="submit" value="Update">
    </form>
  </body>
</html>
)rawliteral";

// ==== Handle root page ====
void handleRoot() {
  server.send(200, "text/html", uploadPage);
}

// ==== Handle firmware upload ====
void handleUpdateUpload() {
  HTTPUpload& upload = server.upload();

  if (upload.status == UPLOAD_FILE_START) {
    Serial.printf("Update Start: %s\n", upload.filename.c_str());
    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { 
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) { 
      Serial.printf("Update Success: %u bytes\nRebooting...\n", upload.totalSize);
    } else {
      Update.printError(Serial);
    }
  }
  yield();
}

// ==== Handle OTA completion ====
void handleUpdateFinished() {
  if (Update.hasError()) {
    server.send(200, "text/plain", "OTA Update Failed!");
  } else {
    server.send(200, "text/plain", "Update Success! Rebooting...");
    delay(1000);
    ESP.restart();
  }
}

void setup() {
  Serial.begin(115200);

  // ==== Start ESP32 as WiFi Access Point ====
  WiFi.mode(WIFI_AP);
  WiFi.softAP(apSSID, apPassword);

  Serial.println("ESP32 running in Access Point mode");
  Serial.print("AP SSID: ");
  Serial.println(apSSID);
  Serial.print("AP Password: ");
  Serial.println(apPassword);
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());  // usually 192.168.4.1

  // Web routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/update", HTTP_POST, handleUpdateFinished, handleUpdateUpload);

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  server.handleClient();
}