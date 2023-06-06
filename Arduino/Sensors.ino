void collectData() {
  int DHTtemp = int(dht.readTemperature());
  int DHThum = int(dht.readHumidity());
  int LDRres = analogRead(0);

  StaticJsonDocument<256> JSONrequest;
  JSONrequest["method"] = "POST";
  JSONrequest["endpoint"] = "reading";
  JsonArray JSONbody = JSONrequest.createNestedArray("body");
  JsonObject reading1 = JSONbody.createNestedObject();
  reading1["sensorID"] = DHT1sensorID;
  reading1["value"] = DHTtemp;
  JsonObject reading2 = JSONbody.createNestedObject();
  reading2["sensorID"] = DHT2sensorID;
  reading2["value"] = DHThum;
  JsonObject reading3 = JSONbody.createNestedObject();
  reading3["sensorID"] = LDRsensorID;
  reading3["value"] = LDRres;
  // Sending JSON
  sendToESP(JSONrequest); 
}