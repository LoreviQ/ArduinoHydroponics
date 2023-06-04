#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <serialStr.h>

SoftwareSerial espSerial(12, 13);
serialStr strReader(&espSerial);
int now = millis(), timer = millis();

void setup() {
  strReader.setCallback(espSerialHandler);
  Serial.begin(9600);
  espSerial.begin(74880);
}

void loop() {
  now = millis();
  idle();
  if (now - timer >= 5000) {
    String data = collectData();

    sendToESP("GET", "", "");

    timer = now;
  }
}

void sendToESP(String method, String endpoint, String body) {
  StaticJsonDocument<64> doc;
  doc["method"] = method;
  doc["endpoint"] = endpoint;
  if (body != "") {
    doc["body"] = body;
  }
  String stringToSend;
  serializeJson(doc, stringToSend);
  Serial.println("Sending JSON: " + stringToSend);
  espSerial.println(stringToSend);
}

  /*
  StaticJsonDocument<48> doc;
  doc["name"] = String("Arduino") + String(random(100,1000));
  doc["SN"] = String(random(1000,10000));
  String body;
  serializeJson(doc, body);
  String postResponse = API.post("", body);
  Serial.println(postResponse);
  */