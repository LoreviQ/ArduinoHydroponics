String collectData() {
  StaticJsonDocument<192> data;
  data["SensorID"] = "6479f6df0769f8f43d5b851b";
  data["SensorType"] = "DHT22";
  data["Variable"] = "Temperature";
  data["Unit"] = "Centigrade";
  data["Reading"] = "24";
  String output;
  serializeJson(data, output);
  return output;
}