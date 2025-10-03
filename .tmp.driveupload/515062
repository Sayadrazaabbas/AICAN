#include <ESPmDNS.h>
#include <Update.h>
AsyncWebServer ota_server(81); // OTA SERVER
const char* host = "OTA";

//Function Decalration
bool testWifi(void);
void launchWeb(void);
void setupAP(void);

//////////////////////////////OTA CODE UPLOAD HTML//////////////////////////////
/*
   Login page
*/
const char* loginIndex =
  "<form name='loginForm'>"
  "<table width='20%' bgcolor='87CEEB' align='center'>"
  "<tr>"
  "<td colspan=2>"
  "<center><font size=4><b>PH UPDATION CENTER</b></font></center>"
  "<br>"
  "</td>"
  "<br>"
  "<br>"
  "</tr>"
  "<td>Username:</td>"
  "<td><input type='text' size=25 name='userid'><br></td>"
  "</tr>"
  "<br>"
  "<br>"
  "<tr>"
  "<td>Password:</td>"
  "<td><input type='Password' size=25 name='pwd'><br></td>"
  "<br>"
  "<br>"
  "</tr>"
  "<tr>"
  "<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
  "</tr>"
  "</table>"
  "</form>"
  "<script>"
  "function check(form)"
  "{"
  "if(form.userid.value=='aican' && form.pwd.value=='raspberry')"
  "{"
  "window.open('/ota_serverIndex')"
  "}"
  "else"
  "{"
  " alert('Error Password or Username')/*displays error message*/"
  "}"
  "}"
  "</script>";
/*
   ota_server Index Page
*/

const char* ota_serverIndex =
  "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
  "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
  "<input type='file' name='update'>"
  "<input type='submit' value='Update'>"
  "</form>"
  "<div id='prg'>progress: 0%</div>"
  "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')"
  "},"
  "error: function (a, b, c) {"
  "}"
  "});"
  "});"
  "</script>";

////////////////////////////// END OF OTA-CODE-UPLOAD HTML//////////////////////////////


void setup_ota_server(){
  WiFi.begin("AICAN", "12345678");
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("AICAN");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Port  81:");
  Serial.println("SSID:-  aican");
  Serial.println("Password:-  raspberry");
  /*use mdns for host name resolution*/
  ip = WiFi.localIP();
  if (!MDNS.begin(host)) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      (1000);
    }
  }
  Serial.println("mDNS responder started");
  /*return index page which is stored in ota_serverIndex */
 // Index page
  
  
  ota_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", loginIndex);
  });

 ota_server.on("/ota_serverIndex", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", ota_serverIndex);
  });

 // OTA Upload handling
  ota_server.on("/update", HTTP_POST,
    [](AsyncWebServerRequest *request){
      bool ok = !Update.hasError();
      request->send(200, "text/plain", ok ? "OK" : "FAIL");
      if (ok) {
        Serial.println("Update complete, restarting...");
        delay(500);
        ESP.restart();
      }
    },
    [](AsyncWebServerRequest *request, const String& filename, size_t index, 
       uint8_t *data, size_t len, bool final){
      if (!index) {
        Serial.printf("Update Start: %s\n", filename.c_str());
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
          Update.printError(Serial);
        }
      }
      if (Update.write(data, len) != len) {
        Update.printError(Serial);
      }
      if (final) {
        if (Update.end(true)) {
          Serial.printf("Update Success: %u bytes\n", index + len);
        } else {
          Update.printError(Serial);
        }
      }
    });

  ota_server.begin();
}
