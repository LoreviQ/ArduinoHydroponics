void collectData() {
  StaticJsonDocument<256> JSONrequest;
  JSONrequest["method"] = "POST";
  JSONrequest["endpoint"] = "reading";
  JsonArray JSONbody = JSONrequest.createNestedArray("body");
  JsonObject reading1 = JSONbody.createNestedObject();
  reading1["sensorID"] = DHT1sensorID;
  reading1["value"] = random(10, 40);
  JsonObject reading2 = JSONbody.createNestedObject();
  reading2["sensorID"] = DHT2sensorID;
  reading2["value"] = random(50, 100);
  JsonObject reading3 = JSONbody.createNestedObject();
  reading3["sensorID"] = LDRsensorID;
  reading3["value"] = random(100, 300);
  // Sending JSON
  sendToESP(JSONrequest); 
}