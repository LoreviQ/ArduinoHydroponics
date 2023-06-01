#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define STASSID "ssid"
#define STAPSK "password"

void setup() {
    Serial.begin(115200);
    Serial.println("Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(STASSID, STAPSK);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
    ArduinoOTA.setPort(8266);
    ArduinoOTA.setHostname("LocalTest");
    ArduinoOTA.setPassword("admin");
    ArduinoOTA.onStart( [] () {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
        } else {  // U_FS
            type = "filesystem";
        }
        // NOTE: if updating FS this would be the place to unmount FS using FS.end()
        Serial.println("Start updating " + type); 
    });
    ArduinoOTA.onEnd( [] () { 
        Serial.println("\nEnd"); 
    });
    ArduinoOTA.onProgress( [] (unsigned int progress, unsigned int total) { 
        Serial.printf("Progress: %u%%\r", (progress / (total / 100))); 
    });
    ArduinoOTA.onError( [] (ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
    });
    ArduinoOTA.begin();
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("This was prgrammed OTA - Version 1.0.1");
}

void loop() {
    ArduinoOTA.handle();
}
