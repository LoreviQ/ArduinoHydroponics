void initializeArduino() {
  StaticJsonDocument<256> JSONrequest;
  if (strcmp(arduinoID, "null") == 0) { // Setup Arduino
    Serial.println("Initializing Arduino");
    // Creating JSON
    JSONrequest["method"] = "POST";
    JSONrequest["endpoint"] = "setup/arduino";
    JsonObject JSONbody = JSONrequest.createNestedObject("body");
    JSONbody["name"] = names[0];
    // Sending JSON
    sendToESP(JSONrequest); 
  } else { 
    for (int i=1; i < numDevices; i++) { // Setup Sensors
      if (strcmp(ids[i], "null") == 0){ 
        Serial.print("Initializing Sensor ");
        Serial.println(i);
        // Creating JSON
        JSONrequest["method"] = "POST";
        JSONrequest["endpoint"] = "setup/sensor";
        JsonObject JSONbody = JSONrequest.createNestedObject("body");
        JSONbody["arduinoID"] = arduinoID;
        JSONbody["name"] = names[i];
        JSONbody["sensorType"] = types[i];
        //JSONbody["variable"] = variables[i];
        //JSONbody["unit"] = units[i];
        // Sending JSON
        sendToESP(JSONrequest); 
        break;
      } else if (i == numDevices-1) {
        initComplete = true; // Stop initialization
      }
    } 
  }
}