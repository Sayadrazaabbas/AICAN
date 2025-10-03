#define AP_SSID "AICAN"
#define AP_PASS "12345678"
//Function Declaration
#define ENCODER_PIN_BUTTON 23
WebServer server(83);  //WIFI SERVER
bool testWifi(void);
void launchWeb(void);
void setupAP(void);
void createWebServer(void);

String st;
String content;
String esid;
String epass = "";
int statusCode;
///////////////////----Fuctions used for WiFi credentials saving and connecting to it which you do not need to change
void connect_wifi() {
  WiFi.begin(esid.c_str(), epass.c_str());
  int count = 0;
  while (WiFi.status() != WL_CONNECTED && count < 4) {
    Serial.println("WL not connected, trying again...");
    WiFi.begin(esid.c_str(), epass.c_str());
    count++;
    delay(1000);
  }
  Serial.println("WL Connected");
}

void wifi_ip() {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
  }
  else {
    Serial.println("WiFi connected");
    Serial.print("ESP32 IP address: ");
    Serial.println(WiFi.localIP());
  }

}

void read_wifi_eeprom() {
  Serial.println("Reading EEPROM ssid");
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  //Serial.println("Reading EEPROM pass");

  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);
}

void check_wifi_config() {
  int t = 1;
  if (digitalRead(14) == LOW && t == 0) { ///////CHANGE TO LOW
    WiFi.disconnect();
    Serial.println("Connection Status Negative / 14 LOW");
    Serial.println("Turning the HotSpot On");
    setupAP();// Setup HotSpot
    launchWeb();


    while ((WiFi.status() != WL_CONNECTED)) {
      Serial.println(".");
      //      digitalWrite(26, HIGH);
      //      delay(500);
      //      digitalWrite(26, LOW);
      //      delay(500);
      server.handleClient();
      yield();
    }
  }
  delay(1000);
}
bool testWifi_init(void)
{
  int c = 0;
  //Serial.println("Waiting for Wifi to connect");
  while ( c < 10 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(1000);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

bool testWifi(void)
{
  int c = 0;
  //Serial.println("Waiting for Wifi to connect");
  while ( c < 2 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(1000);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

void launchWeb()
{
  Serial.println("");
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}

void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      //Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);

    st += ")";
    //st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.println("Initializing_softap_for_wifi credentials_modification");
  launchWeb();
  Serial.println("over");
}

void createWebServer()
{
  {
    server.on("/", []() {

      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>Device Setup Page";
      content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
      content += ipStr;
      content += "<p>";
      content += st;
      content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><label>Password: </label><input name='pass' length=64></p><label> IP: </label><input name='ip' length=32><label> Machine ID: </label><input name='mid' length=64><label> Device ID: </label><input name='did' length=64><input type='submit'></form></form>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    server.on("/scan", []() {
      //setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

      content = "<!DOCTYPE HTML>\r\n<html>go back";
      server.send(200, "text/html", content);
    });

    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      ip = server.arg("ip");
      mid = server.arg("mid");
      did = server.arg("did");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");
        Serial.println(ip);
        Serial.println("");
        Serial.println(mid);
        Serial.println("");
        //        Serial.println(did);
        //        Serial.println("");

        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.print("Wrote: ");
          Serial.println(qsid[i]);
        }

        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
        Serial.println("writing IP, MID, DID:");
        if (ip.length() > 0 || mid.length() > 0 || did.length() > 0) {
          for (int i = 100; i < 150; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < ip.length(); i++)  {
            EEPROM.write(100 + i, ip[i]);
          }
          for (int i = 0; i < mid.length(); i++) {
            EEPROM.write(120 + i, mid[i]);
          }
          for (int i = 0; i < did.length(); i++) {
            EEPROM.write(130 + i, did[i]);
          }
        }
        EEPROM.commit();

        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
        ESP.restart();
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);

    });
  }
}
////////////////////////////////////////////////////////////////////////////////////
