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
serialStr strReader(&Serial, '\n', 256);
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
  StaticJsonDocument<256> request;
  DeserializationError err = deserializeJson(request, inStr);
  if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.f_str());
  } else {
    if (request["method"] == "GET") {
      // Make request
      String response = API.get(request["endpoint"]);

      //Pass on server response
      Serial.println("Printing response from Server");
      Serial.println(response);
    } else if (request["method"] == "POST") {
      // Make request
      String response = API.post(request["endpoint"], request["body"]);
      // Create and send Response
      Serial.println("ID: " + response);
    } else {
      Serial.println("Invalid JSON");
    }
  }
}