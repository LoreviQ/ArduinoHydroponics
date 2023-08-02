void collectData() {
  bool setRandom = RANDOM_SENSORS;
  int readings[numDevices-1]; // DHT22-Temp, DHT22-Hum, LDR, CO2, Turbidity

  if (setRandom == true) { //Random Data
    readings[0] = random(10,40); // DHT22-Temp
    readings[1] = random(50,100); // DHT22-Hum
    readings[2] = random(100,300); // LDR
    readings[3] = random(30,200); // CO2
    readings[4] = random(30,200); // Turbidity
    readings[5] = random(100,300); // LDR
    readings[6] = random(30,200); // CO2
    readings[7] = random(30,200); // Turbidity
  } 

  // Get Data from Sensors
  else {
    readings[0] = int(dht.readTemperature()); // DHT22-Temp
    readings[1] = int(dht.readHumidity()); // DHT22-Hum
    readings[2] = int(dht.readTemperature()); // DHT22-Temp
    readings[3] = int(dht.readHumidity()); // DHT22-Hum
    readings[4] = analogRead(0); // LDR1
    readings[5] = analogRead(1); // LDR2
    // CO2
    mhzSerial1.begin(9600);
    if (mhz19b1.isReady()) {
      readings[6] = mhz19b1.readCO2();
    } else {
      Serial.println(F("CO2 sensor not yet ready..."));
      if (mhz19b1.isWarmingUp()) {
        Serial.println(F("CO2 sensor still warming up..."));
      }
      readings[6] = -1;
    }
    mhzSerial2.begin(9600);
    if (mhz19b2.isReady()) {
      readings[6] = mhz19b2.readCO2();
    } else {
      Serial.println(F("CO2 sensor not yet ready..."));
      if (mhz19b2.isWarmingUp()) {
        Serial.println(F("CO2 sensor still warming up..."));
      }
      readings[6] = -1;
    }
    espSerial.begin(74880);
  }
  
  // Send data 2 readings at a time with 2 secs inbetween;
  for (int i=0; i < numDevices-1; i = i + 2) {
    StaticJsonDocument<256> JSONrequest;
    JSONrequest["method"] = "POST";
    JSONrequest["endpoint"] = "reading";
    JsonArray JSONbody = JSONrequest.createNestedArray("body");
    JsonObject reading1 = JSONbody.createNestedObject();
    reading1["sensorID"] = ids[i+1];
    reading1["value"] = readings[i];
    if (i+1 != numDevices-1) {
      JsonObject reading2 = JSONbody.createNestedObject();
      reading2["sensorID"] = ids[i+2];
      reading2["value"] = readings[i+1];
    }
    // Sending JSON
    sendToESP(JSONrequest);
    int nowR = millis(), timerR = millis();
    while (nowR - timerR < 2000) {
      idle();
      nowR = millis();
    }
  }
}