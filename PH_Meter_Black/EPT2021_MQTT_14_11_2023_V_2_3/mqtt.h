//#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char *ssid = "AICAN";          // Replace with your WiFi network name
const char *password = "12345678";      // Replace with your WiFi password
const char *mqtt_server = "192.168.2.4"; // MQTT Broker IP address
const int mqtt_port = 1883;
const char *mqtt_username = "";         // Replace with your MQTT username
const char *mqtt_password = "";         // Replace with your MQTT password
char valueStr[20];
WiFiClient espClient;
PubSubClient client(espClient);
void callback(char* topic, byte* payload, unsigned int length) {
   Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
   Serial.println("TOPIC:-");
   Serial.println(topic);
   Serial.println("MY AUTOLOG TOPIC");
   Serial.println(AUTO_LOG);
   Serial.print("PAYLOAD:-");
   Serial.println((char*)payload);
   Serial.print("Length:-");
   Serial.println(length);
   Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");



  for (int i = 0; i < length && i < sizeof(valueStr) - 1; i++) {
    valueStr[i] = (char)payload[i];
    valueStr[i + 1] = '\0'; // Null-terminate the string
  }
  Serial.println("#######################################################");
  Serial.println(topic);
  Serial.print(":-");
  Serial.println(valueStr);
  Serial.println("#######################################################");


  ////////////////////////Calibration button /////////////////////////
  if (strcmp(topic, CAL.c_str()) == 0) {
    calButton = atoi(valueStr);
    Serial.println("#######################################################");
    Serial.println("calButton:-");
    Serial.println(calButton);
    Serial.println("#######################################################");
    if (calButton == 10 || calButton == 20 || calButton == 30 || calButton == 40 || calButton == 50) {
      start_ph_cal = 1;
    }
    if (calButton == 0) {
      start_ph_cal = 0;
    }
  }
  else if (strcmp(topic, AUTO_LOG.c_str()) == 0) {

    log_mode = atoi(valueStr);
    Serial.println("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
    Serial.println("log_mode");
    Serial.println(log_mode);
    Serial.println("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
  } else if (strcmp(topic, B_1.c_str()) == 0) {
    bufferValue[0] = atof(valueStr);
    ongoingbuffer = 0;
    ongoingbuffer = bufferValue[0];
    Serial.print("#######################################################");
    Serial.print("bufferValue[0]");
    Serial.println(bufferValue[0]);
    Serial.println("#######################################################");
    if (cal_mode == 2) {
      EEPROM.put(240, bufferValue[0]);
      EEPROM.commit();
    }
    else if (cal_mode == 1) {
      EEPROM.put(470, bufferValue3[0]);
      EEPROM.commit();
    }
  } else if (strcmp(topic, B_2.c_str()) == 0) {
    Serial.print("#######################################################");
    bufferValue[1] = atof(valueStr);
    ongoingbuffer = 0;
    ongoingbuffer = bufferValue[1];
    Serial.println("#######################################################");
    Serial.print("bufferValue[1]");
    Serial.println(bufferValue[1]);
    Serial.println("#######################################################");

    if (cal_mode == 2) {
      EEPROM.put(246, bufferValue[1]);
      EEPROM.commit();
    }
    else if (cal_mode == 1) {
      EEPROM.put(476, bufferValue3[1]);
      EEPROM.commit();
    }
  } else if (strcmp(topic, B_3.c_str()) == 0) {
    Serial.print("bufferValue[2]");
    bufferValue[2] = atof(valueStr);
    ongoingbuffer = 0;
    ongoingbuffer = bufferValue[2];
    Serial.println("#######################################################");
    Serial.print("bufferValue[2]");
    Serial.println(bufferValue[2]);
    Serial.println("#######################################################");
    if (cal_mode == 2) {
      EEPROM.put(252, bufferValue[2]);
      EEPROM.commit();
    }
    else if (cal_mode == 1) {
      EEPROM.put(482, bufferValue3[2]);
      EEPROM.commit();
    }
  } else if (strcmp(topic, B_4.c_str()) == 0) {
    Serial.print("bufferValue[3]");
    bufferValue[3] = atof(valueStr);
    ongoingbuffer = 0;
    ongoingbuffer = bufferValue[3];
    Serial.println("#######################################################");
    Serial.print(bufferValue[3]);
    Serial.println("#######################################################");
    EEPROM.put(258, bufferValue[3]);
    EEPROM.commit();
  } else if (strcmp(topic, B_5.c_str()) == 0) {
    bufferValue[4] = atof(valueStr);
    ongoingbuffer = 0;
    ongoingbuffer = bufferValue[4];
    Serial.println("#######################################################");
    Serial.print("bufferValue[4]");
    Serial.println(bufferValue[4]);
    Serial.println("#######################################################");
    EEPROM.put(264, bufferValue[4]);
    EEPROM.commit();
  } else if (strcmp(topic, T_SET.c_str()) == 0) {
    Serial.println("#######################################################");
    Serial.print("RO");
    Ro = atoi(valueStr);
    Serial.println(Ro);
    Serial.println("#######################################################");
    EEPROM.put(450, Ro);
    EEPROM.commit();
  } else if (strcmp(topic, ATC.c_str()) == 0) {
    atc_var = atoi(valueStr);
    Serial.println("#######################################################");
    Serial.print("atc_var");
    Serial.println(atc_var);
    Serial.println("#######################################################");
  } else if (strcmp(topic, CAL_MODE.c_str()) == 0) {
    cal_mode = atoi(valueStr);
    Serial.println("######################### Pay Load ##########################");
    Serial.print("cal_mode:-   ");
    Serial.println(cal_mode);
    Serial.println("#######################################################");
    EEPROM.put(410, cal_mode);
    EEPROM.commit();
  }
}

////////////////////////////////////////////

void Subscriptions()
{
  client.subscribe(CAL_MODE.c_str());
  Serial.println("Subscribed to: " + String(CAL_MODE));

  client.subscribe(CAL.c_str());
  Serial.println("Subscribed to: " + String(CAL));
  client.subscribe(ATC.c_str());
  Serial.println("Subscribed to: " + String(ATC));
  client.subscribe(T_SET.c_str());
  Serial.println("Subscribed to: " + String(T_SET));
  
  client.subscribe(maxMV1.c_str());
  Serial.println("Subscribed to: " + String(maxMV1));
  client.subscribe(maxMV2.c_str());
  client.subscribe(maxMV3.c_str());
  client.subscribe(maxMV4.c_str());
  client.subscribe(maxMV5.c_str());

  client.subscribe(minMV1.c_str());
  client.subscribe(minMV2.c_str());
  client.subscribe(minMV3.c_str());
  client.subscribe(minMV4.c_str());
  client.subscribe(minMV5.c_str());

  client.subscribe(B_1.c_str());
  client.subscribe(B_2.c_str());
  client.subscribe(B_3.c_str());
  client.subscribe(B_4.c_str());
  client.subscribe(B_5.c_str());
  client.subscribe(AUTO_LOG.c_str());
}





//////////////////////////////Setup started //////////////////////////////
void mqtt_setup() {
  int count = 0;

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  while (!client.connected() && count != 5) {
    String client_id = did;
    client_id += String(WiFi.macAddress()); // Convert const char* to String before concatenation

    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("MQTT broker connected");
    } else {
      Serial.print("Failed to connect to MQTT broker, state: ");
      Serial.println(client.state());
      delay(1000 * count);
    }
    count++;
  }
}
//////////////////////////////setup end ////////////////////////////////////


void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    String client_id = did;
    client_id += String(WiFi.macAddress()); // Convert const char* to String before concatenation

    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("MQTT connected");
      // Subscribe to topics and publish messages here, if needed
      Subscriptions();
    } else {
      Serial.print("MQTT connection failed, state: ");
      Serial.println(client.state());
      delay(2000); // Wait for 2 seconds before retrying
    }
  }
}
