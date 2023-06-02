#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include "API-Handler.h"
#include "env.h"

APIHandler API("http://35.176.73.55/");

void setup() {
  Serial.begin(115200);
  Serial.println("\nBooting");
  wifiConnect();
  OTASetup();
}

void loop() {
  ArduinoOTA.handle();
  delay(5000);
  
  String getResponse = API.get("");
  Serial.println(getResponse);

  StaticJsonDocument<48> doc;
  doc["name"] = String("Arduino") + String(random(100,1000));
  doc["SN"] = String(random(1000,10000));
  String body;
  serializeJson(doc, body);
  String postResponse = API.post("", body);
  Serial.println(postResponse);
}
 