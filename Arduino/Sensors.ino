void collectData() {
  bool setRandom = RANDOM_SENSORS;
  int DHTtemp;
  int DHThum;
  int LDRres;
  int CO2;
  // Get Data
  if (setRandom == true) {
    DHTtemp = random(10,40);
    DHThum = random(50,100);
    LDRres = random(100,300);
    CO2 = random(30,200);
  } else {
    DHTtemp = int(dht.readTemperature());
    DHThum = int(dht.readHumidity());
    LDRres = analogRead(0);
    // CO2
    mhzSerial.begin(9600);
    if (mhz19b.isReady()) {
      CO2 = mhz19b.readCO2();
    } else {
      Serial.println(F("CO2 sensor not yet ready..."));
      if (mhz19b.isWarmingUp()) {
        Serial.println(F("CO2 sensor still warming up..."));
      }
      CO2 = -1;
    }
    espSerial.begin(74880);
  }

  int readings[] = {DHTtemp, DHThum, LDRres, CO2};
  size_t numReadings = sizeof(readings) / sizeof(readings[0]);
  // Send data 2 readings at a time with 2 secs inbetween;
  for (int i=0; i < numReadings; i = i + 2) {
    StaticJsonDocument<256> JSONrequest;
    JSONrequest["method"] = "POST";
    JSONrequest["endpoint"] = "reading";
    JsonArray JSONbody = JSONrequest.createNestedArray("body");
    JsonObject reading1 = JSONbody.createNestedObject();
    reading1["sensorID"] = ids[i+1];
    reading1["value"] = readings[i];
    if (i+1 != numReadings) {
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