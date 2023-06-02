#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include <env.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Booting");
    wifiConnect();
    OTASetup();
}

void loop() {
    ArduinoOTA.handle();
}
 