#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <serialStr.h>
#include "API-Handler.h"
#include "env.h"

APIHandler API("http://35.176.73.55/");
serialStr strReader;
int now = millis(), timer = millis();

void setup() {
  strReader.setCallback(serialHandler);
  Serial.begin(74880);
  Serial.println("\nBooting");
  wifiConnect();
  OTASetup();
}

void loop() {
  idle();
  ArduinoOTA.handle();
}

void serialHandler(char* inStr) {
  Serial.println(String("Recieved : ") + String(inStr));
  StaticJsonDocument<64> command;
  DeserializationError err = deserializeJson(command, inStr);
  if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.f_str());
  }
  if (command["method"] == "GET") {
    String response = API.get(command["endpoint"]);
    Serial.println("Printing response from Server");
    Serial.println(response);
  }
}