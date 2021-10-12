#define GLED   D5
#define BLED   D6
#define RLED   D7
#define Buzzer D8
#define Lock   D1
bool cnn;




String data,ipadd;
#include <rdm6300.h>
#define RDM6300_RX_PIN 4 // read the SoftwareSerial doc above! may need to change this pin to 10...
Rdm6300 rdm6300;     


#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>


#ifndef STASSID
#define STASSID "jimmy"
#define STAPSK  "neways007"
#endif



String payload ;
const char* serverName = "http://10.100.93.11/super_home/json/data-information-pi/select";


const char* ssid = STASSID;
const char* password = STAPSK;

void setup() {

  pinMode(GLED, OUTPUT);

  pinMode(RLED, OUTPUT);


  pinMode(BLED, OUTPUT);

  pinMode(Buzzer, OUTPUT);

  pinMode(Lock, OUTPUT);
  
//intially all pin are off
  digitalWrite(GLED, HIGH);
  digitalWrite(BLED, HIGH);
  digitalWrite(RLED, HIGH);
  digitalWrite(Buzzer, LOW);
  digitalWrite(Lock, HIGH);
  
  rdm6300.begin(RDM6300_RX_PIN);

  Serial.println("\nPlace RFID tag near the rdm6300...");

  
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

   ArduinoOTA.setPassword("jimmy007");


  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");

  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();

    if (rdm6300.update())
 {
  data="000";
  data+=String(rdm6300.get_tag_id(), DEC);
   rdm6300.end();
   rdm6300.begin(RDM6300_RX_PIN);

  Serial.println(data);
  database();
   
 
 }
 delay(1000);
 
 
  
}
