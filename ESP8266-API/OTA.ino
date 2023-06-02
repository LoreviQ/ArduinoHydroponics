void OTASetup() {
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
        Serial.println("Progress: %u%%\r", (progress / (total / 100))); 
    });
    ArduinoOTA.onError( [] (ota_error_t error) {
        Serial.println("Error[%u]: ", error);
    });
    ArduinoOTA.begin();
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("This was prgrammed OTA - Version 1.0.2");
}