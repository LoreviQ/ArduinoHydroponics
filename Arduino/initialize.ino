void initializeArduino() {
  StaticJsonDocument<256> JSONrequest;
  // Setup Arduino
  if (strcmp(arduinoID, "null") == 0) { 
    Serial.println(F("Initializing Arduino"));
    // Creating JSON
    JSONrequest["method"] = "POST";
    JSONrequest["endpoint"] = "setup/arduino";
    JsonObject JSONbody = JSONrequest.createNestedObject("body");
    strcpy_P(buffer, (char*)pgm_read_word(&(names[0])));
    JSONbody["name"] = buffer;
    // Sending JSON
    sendToESP(JSONrequest); 
  } else { 
    // Setup Sensors
    for (int i=1; i < numDevices; i++) {
      if (strcmp(ids[i], "null") == 0){ 
        Serial.print(F("Initializing Sensor "));
        Serial.println(i);
        // Creating JSON
        JSONrequest["method"] = "POST";
        JSONrequest["endpoint"] = "setup/sensor";
        JsonObject JSONbody = JSONrequest.createNestedObject("body");
        JSONbody["arduinoID"] = arduinoID;
        strcpy_P(buffer, (char*)pgm_read_word(&(names[i])));
        JSONbody["name"] = buffer;
        strcpy_P(buffer, (char*)pgm_read_word(&(types[i-1])));
        JSONbody["sensorType"] = buffer;
        // Sending JSON
        sendToESP(JSONrequest); 
        break;
      } else if (i == numDevices-1) {
        initComplete = true; // Stop initialization
      }
    } 
  }
}