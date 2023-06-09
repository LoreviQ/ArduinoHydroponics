#include <ArduinoJson.h>

int now = millis(), timer = millis();
char buffer[25];
const char arduino[] PROGMEM = {"OJ-test"};
const char S1name[] PROGMEM = {"DHT22-Temp"};
const char S2name[] PROGMEM = {"DHT22-Hum"};
const char S3name[] PROGMEM = {"LDR"};
const char S4name[] PROGMEM = {"CO2"};
const char * const names[] PROGMEM = {arduino, S1name, S2name, S3name, S4name};
const size_t count = sizeof(names)/sizeof(const char * );

void setup() {
  Serial.begin(9600);
}

void loop() {
  now = millis();
  if (now - timer >= 5000) {
    Serial.println();
    Serial.println(count);
    testPrint();
    testJSON();
    timer = now;    
  }
}

void testPrint() {
  Serial.println(F("Testing Print Functions"));
  for (int i = 0; i < 5; i++) {
    Serial.println((__FlashStringHelper*)pgm_read_word(&names[i]));
  }
}

void testJSON() {
  Serial.println(F("Testing JSON Functions"));
  for (int i = 0; i < 5; i++) {
    StaticJsonDocument<64> doc;
    strcpy_P(buffer, (char*)pgm_read_word(&(names[i])));
    doc["name"] = buffer;
    char output[64];
    serializeJson(doc, output);
    Serial.println(output);
  }
}