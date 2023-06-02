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
    Serial.println("Booting");
    wifiConnect();
    OTASetup();

}

void loop() {
    ArduinoOTA.handle();
    delay(5000);
    String payload = API.get("");
    Serial.println(payload);
}
 